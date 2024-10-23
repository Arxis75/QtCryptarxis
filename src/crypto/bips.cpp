#include <crypto/bips.h>
#include <crypto/bip39_dictionnary.h>
#include <data/StrByteSet.h>
#include <data/Tools.h>

using namespace BIP39;

//----------------------------------------------------------- BIP32 -----------------------------------------------------------------

Pubkey::Pubkey(const EllipticCurve& curve)
    : m_ecc(curve)
{ }

Pubkey::Pubkey(const Point& p, const EllipticCurve &curve)
    : m_ecc(curve)
    , m_point(p)
{ }

Pubkey::Pubkey(const Point &p, const ByteSet &cc, const EllipticCurve &curve)
    : m_ecc(curve)
    , m_point(p)
    , m_chaincode(cc)
{ }

Pubkey::Pubkey(const Pubkey &key) 
    : m_ecc(key.m_ecc)
    , m_point(key.m_point)
    , m_chaincode(key.m_chaincode)
{ }

Pubkey::Pubkey(const ByteSet &formated_key, const Pubkey::Format f, const EllipticCurve &curve)
    : m_ecc(curve)
{
    IntByteSet tmp(formated_key);
    if( f == Format::PREFIXED_X )
    {
        assert(tmp.byteSize() <= 33);
        bool y_imparity = (tmp.pop_front(1) % 2);
        Element x = tmp;
        m_point = m_ecc.getPointFromX(x, y_imparity);
    }
    else if( f == Format::PREFIXED_XY )
    {
        assert(tmp.byteSize() == 65);
        tmp.pop_front(1);
        Element x = tmp.pop_front(32);
        Element y = tmp.pop_front(32);
        m_point = Point(x, y);
    }
    else //if( f == Format::XY )
    {
        assert(tmp.byteSize() == 64);
        Element x = tmp.pop_front(32);
        Element y = tmp.pop_front(32);
        m_point = Point(x, y);
    }    
}

const ByteSet Pubkey::getKey(Format f) const
{   
    uint32_t point_bitsize = sizeInBytes(m_ecc.getGeneratorOrder())<<3;
    
    Integer retval;
    if( f == Format::PREFIXED_X )
    {
        retval = ((m_point.getY() % 2) ? 0x03 : 0x02);
        retval <<= point_bitsize;
        retval |= m_point.getX();
        return IntByteSet(retval, 33);
    }
    else if( f == Format::PREFIXED_XY )
    {
        retval = 0x04;
        retval <<= point_bitsize;
        retval |= m_point.getX();
        retval <<= point_bitsize;
        retval |= m_point.getY();
        return IntByteSet(retval, 65);
    }
    else //if( f == Format::XY )
    {
        retval = m_point.getX();
        retval <<= point_bitsize;
        retval |= m_point.getY();
        return IntByteSet(retval, 64);
    }
}

uint32_t Pubkey::getFormatByteSize(Format f) const
{
    switch(f)
    {
        case Format::PREFIXED_X:
            return 1 + sizeInBytes(m_ecc.getGeneratorOrder());
        case Format::PREFIXED_XY:
            return 1 +  (sizeInBytes(m_ecc.getGeneratorOrder())<<1);
        default:
            return sizeInBytes(m_ecc.getGeneratorOrder())<<1;
    }
}

const ByteSet Pubkey::getAddress() const
{
    hash256 h = ethash::keccak256(ArrayByteSet(getKey(Format::XY)), getFormatByteSize(Format::XY));
    return ArrayByteSet(&h.bytes[32 - 20], 20);
}

//-----------------------------------------------------------------------------------------------------------------

Signature::Signature(const Integer& r, const Integer& s, const bool imparity, const EllipticCurve& curve)
    : EllipticCurve(curve)
    , m_r(r)
    , m_s(s)
    , m_smax(curve.getGeneratorOrder()>>1)   //Cf EIP-2
    , m_imparity(imparity)
{ }

void Signature::fixMalleability()
{
    if(!isMalleabilityFixed())
    {
        m_s = getGeneratorOrder() - m_s;
        m_imparity = !m_imparity;
    }
}

bool Signature::isValid(const ByteSet &h, const ByteSet &from_address, const bool enforce_eip2) const
{
    Pubkey key;
    return ( from_address.byteSize() == 20 &&
             (m_s <= m_smax || !enforce_eip2) &&
             ecrecover(key, h, from_address) && from_address == key.getAddress() );
}

bool Signature::ecrecover(Pubkey &key, const ByteSet &h, const ByteSet &from_address) const
{
    bool ret = false;
    Point Q_candidate;
    if( recover(Q_candidate, h, m_r, m_s, m_imparity, false) )
    {
        Pubkey key_candidate(Q_candidate, (*this));
        if( from_address.byteSize() == 20 && key_candidate.getAddress() != from_address )
        {
            if( recover(Q_candidate, h, m_r, m_s, m_imparity, true) )
            {
                key_candidate = Pubkey(Q_candidate, (*this));
                if(key_candidate.getAddress() == from_address)
                {
                    key = key_candidate;
                    ret = true;
                }
            }
        }
        else
        {
            key = key_candidate;
            ret = (key_candidate.getAddress() == from_address || from_address.byteSize() == 0);
        }
    }
    return ret;
}

void Signature::print() const
{
    cout << "Signature: " << endl;
    cout << "   r = " << hex << "0x" << get_r() << endl;
    cout << "   s = " << hex << "0x" << get_s() << endl;
    cout << "   imparity = " << get_imparity() << endl;
}

//-----------------------------------------------------------------------------------------------------------------

Privkey::Privkey(const Privkey& privkey)
    : m_pubkey(privkey.m_pubkey)
    , m_secret(privkey.m_secret)
{ }

Privkey::Privkey(const Privkey& parent_privkey, const int32_t index, const bool hardened)
{
    assert(index >= 0);

    IntByteSet parent_data;
    IntByteSet parent_cc(parent_privkey.getChainCode());
    uint32_t suffix = index;
    if(!hardened)
        parent_data = IntByteSet(parent_privkey.getPubKey().getKey(Pubkey::Format::PREFIXED_X));
    else
    {
        parent_data = IntByteSet(parent_privkey.getSecret(), 33);   // 0x00 prefix + 32bytes
        suffix += 0x80000000;
    }      
    //cout << parent_data << endl;
    parent_data.push_back(suffix, 4);
   
    IntByteSet digest(0, 64);
    uint32_t dilen;
    unsigned char *res = HMAC( EVP_sha512(),
                               parent_cc, 32,
                               parent_data, 33 + 4,
                               digest, &dilen);
    if (res && dilen == 64)
    {
        //cout << "BIP32 " << dec << index << (hardened ? "'" : "") << " raw (hex): " << digest << dec << endl;
    
        EllipticCurve curve = parent_privkey.getCurve();
        m_secret = (IntByteSet)ArrayByteSet(&digest[0], 32);               // first 32 bytes/64 = secret
        m_secret += parent_privkey.getSecret();
        m_secret %= curve.getGeneratorOrder();

        ArrayByteSet cc(&digest[32], 32);
        m_pubkey = Pubkey(curve.p_scalar(curve.getGenerator(), m_secret), cc, curve);

        //cout << "BIP32 " << index << (hardened ? "'" : "") << " chain code (hex):  " << hex << m_pubkey.getChainCode() << dec << endl;
        //cout << "BIP32 " << index << (hardened ? "'" : "") << " secret (hex):      " << hex << m_secret << dec << endl;
        //cout << "BIP32 " << index << (hardened ? "'" : "") << " public key (hex): " << hex << m_pubkey.getKey(Pubkey::Format::PREFIXED_X) << dec << endl << endl;
    }
}

Privkey::Privkey(const ByteSet &k, const EllipticCurve& curve)
    : m_secret((IntByteSet)k)
    , m_pubkey(Pubkey(curve.p_scalar(curve.getGenerator(), (IntByteSet)k), curve))
{
    //cout << hex << k << endl;
    //cout << hex << curve.getGeneratorOrder() << endl;
    assert(Integer((IntByteSet)k) > 0 && Integer((IntByteSet)k) < curve.getGeneratorOrder());
}

Privkey::Privkey(const BIP39::Mnemonic& mnc, const char *path, const int32_t account_i, const EllipticCurve& curve)
    : Privkey(mnc.get_seed(), path, account_i, curve)
{ }

Privkey::Privkey(const ByteSet &seed, const char *path, const int32_t account_i, const EllipticCurve& curve)
{
    assert(seed.byteSize() >= 16 && seed.byteSize() <= 64);

    // Cf https://www.openssl.org/docs/manmaster/man3/HMAC.html
    // Cf https://www.openssl.org/docs/manmaster/man3/EVP_sha512.html

    ArrayByteSet digest(64);
    uint32_t dilen;

    unsigned char *res = HMAC( EVP_sha512(),
                            "Bitcoin seed", 12,
                            ArrayByteSet(seed), (seed.byteSize()),
                            digest, &dilen);
    if (res && dilen == 64)
    {
        //cout << "BIP32 Root raw (hex): " << digest << dec << endl;

        m_secret = (IntByteSet)ArrayByteSet(&digest[0], 32); // first 32bytes/64 = secret
        m_secret %= curve.getGeneratorOrder();

        ArrayByteSet cc(&digest[32], 32);
        m_pubkey = Pubkey(curve.p_scalar(curve.getGenerator(), m_secret), cc, curve);

        DerivationPath dp(path);
        (*this) = dp.deriveRootKey(*this, account_i);

        //cout << "BIP32 " << "Root chain code (hex): " << hex << m_pubkey.getChainCode() << dec << endl;
        //cout << "BIP32 " << "Root secret (hex): " << hex << m_secret << dec << endl;
        //cout << "BIP32 " << "Root public key (hex): " << hex << m_pubkey.getKey(Pubkey::Format::PREFIXED_X) << dec << endl << endl;
    }
}

const Signature Privkey::signWithPrefix(const char* msg, const bool enforce_eip2) const
{
    RawStrByteSet t_raw("\u0019Ethereum Signed Message:\n");
    t_raw.push_back(to_string(strlen(msg)));
    t_raw.push_back(msg);

    return sign(t_raw.keccak256(), enforce_eip2);
}

const Signature Privkey::sign(const ByteSet &h, const bool enforce_eip2) const
{
    EllipticCurve ecc = m_pubkey.getCurve();
    Integer n = ecc.getGeneratorOrder();

    Integer k_1;
    bool imparity;
    Integer r;
    uint8_t nonce_to_skip = 0;
    while(true)
    {
        Integer k = ecc.generate_RFC6979_nonce(m_secret, h, nonce_to_skip);
        //cout << hex << "k = 0x" << k << endl;
        inv(k_1, k, n);
        //cout << hex << "k^(-1) = 0x" << k_1 << endl;
        Point R = ecc.p_scalar(ecc.getGenerator(), k);
        //cout << hex << "R = (0x" << R.getX() << ", 0x" << R.getY() << ")" << endl;
        imparity = isOdd(R.getY());
        //cout << "R.y imparity = " << (imparity ? "odd (0x01)" : "even (0x00)") << endl;
        r = R.getX();
        //cout << hex << "r = 0x" << r << endl;
        if(!R.isIdentity() && r>0 && r<n) break;   
        // ECDSA specifies r = Rx%n (Cf p184 "Guide to Elliptic Curve Cryptography")
        // In case of n < Rx < p, Ethereum cannot recover the proper R from r (and consequently the proper PublicKey),
        // as Rx != r (Rx = r + n). There is no information attached to v that might help discriminating this edge-case.
        // => It is mandatory to iterate the nonce generation to find another k satisfying r = Rx.
        nonce_to_skip++;
    }
    Integer s = (k_1 * ((Integer)IntByteSet(h) + (r*m_secret))) % n;
    //cout << hex << "s = k^(-1) . (h + r.x) = 0x" << s << endl;

    Signature sig(r, s, imparity, ecc);
    if(enforce_eip2)
        sig.fixMalleability();

    return sig;
}

const Privkey Privkey::generateRandom(const EllipticCurve &curve)
{
    int retval = -1;
    IntByteSet random_buffer(0, sizeInBytes(curve.getGeneratorOrder()));
    while( random_buffer == 0 || (Integer)random_buffer >= curve.getGeneratorOrder() || retval <= 0 )
        retval = RAND_bytes(random_buffer, random_buffer.byteSize());
    Privkey random_key(random_buffer);
    return random_key;
}

void Privkey::print() const
{
    cout << hex << "0x" << m_secret << endl;
}

//----------------------------------------------------------- BIP39 -----------------------------------------------------------------

Mnemonic::Mnemonic(const size_t entropy_bitsize, const vector<string> *dictionnary)
    : m_pwd("")
{
    div_t d;
    m_dic = (dictionnary ? dictionnary : &BIP39::Dictionary::WordList_english);
    assert(m_dic->size() > 1); // at least 2 elements
    // TOD: verify each element of the dictionnary is unique

    m_went = log2(m_dic->size());
    assert(m_went <= 32); // max word entropy = 32 bits

    m_ent = entropy_bitsize;
    assert(m_ent >= 128); // for security
    d = div(m_ent, 32);
    assert(!d.rem); // multiple of 32

    d = div(m_ent, m_went);
    m_ms = d.quot + 1; // 1 extra word for checksum/alignment
    m_cs = m_went - d.rem;
}

bool Mnemonic::add_entropy(const string& entropy, const uint32_t bitsize, const uint8_t in_base)
{
    bool ret = false;
    if( m_entropy.bitSize() + bitsize <= m_ent)
    {
        m_entropy.push_back(entropy, bitsize);
        ret = true;
    }
    return ret;
}

bool Mnemonic::add_word(const string &word)
{
    bool res = false;
    std::string data = word;
    std::transform(data.begin(), data.end(), data.begin(), ::tolower);
    vector<string>::const_iterator dic_it;
    dic_it = find(m_dic->begin(), m_dic->end(), data);
    if (dic_it != m_dic->end() && m_entropy.bitSize() < m_ent)
    {
        bool is_last_word = (m_entropy.bitSize() + m_went > m_ent);
        uint32_t controlled_went = m_went;
        if (is_last_word)
            controlled_went -= m_cs;
        uint32_t index = distance(m_dic->begin(), dic_it);
        BitSet e(m_entropy);
        e.push_back(index >> (m_went - controlled_went), controlled_went);
        if (!is_last_word || e.sha256().at(0,m_cs).as_uint8() == (index & (0xFF >> (8 - m_cs))))
        {
            m_entropy = e;
            res = true;
        }
    }
    if (!res)
        cout << "invalid word addition!" << endl;
    return res;
}

bool Mnemonic::set_full_word_list(const string &list)
{
    bool res = false;
    clear();
    vector<string> v = split(list, " ");
    if (v.size() == m_ms)
        for (int i = 0; i < v.size(); i++)
        {
            res = add_word(v[i]);
            if (!res)
            {
                clear();
                break;
            }
        }
    return res;
}

void Mnemonic::setPassword(const string& pwd)
{
    m_pwd = pwd;
}

bool Mnemonic::is_valid() const
{
    return (m_entropy.bitSize() == m_ent);
}

void Mnemonic::clear()
{
    m_entropy.clear();
}

const string Mnemonic::get_word_list() const
{
    string ret("");
    uint32_t nth_word;
    div_t d = div(m_entropy.bitSize(), m_went);
    for (int i = 0; i < d.quot; i++)
    {
        if(ret.size() > 0)
            ret += " ";
        ret += m_dic->at(m_entropy.at(i*m_went,m_went).as_uint16());
    }
    if (d.rem && is_valid())
        ret += " " + get_last_word();
    return ret;
}

bool Mnemonic::list_possible_last_word(vector<string> &list) const
{
    bool res = false;
    if (m_entropy.bitSize() == m_went * (m_ms - 1))
    {
        list.clear();
        for (int i = 0; i < (1 << (m_went - m_cs)); i++)
        {
            BitSet tmp(m_entropy);
            tmp.push_back(i, m_went - m_cs);
            list.push_back(m_dic->at((i << m_cs) + tmp.sha256().at(0,m_cs).as_uint8()));
        }
        res = true;
    }
    return res;
}

const string Mnemonic::get_last_word() const
{
    string ret("");
    if (is_valid())
    {
        Integer index = (m_entropy[(m_ms - 1)*m_went, m_went-m_cs] << m_cs) + m_entropy.sha256().at(0, m_cs);
        ret = m_dic->at(index);
    }
    return ret;
}

void Mnemonic::print(bool as_index_list) const
{
    if (as_index_list)
        cout << m_entropy << endl;
    else
        cout << get_word_list() << endl;
}

const ByteSet Mnemonic::get_seed() const
{
    return get_seed(m_pwd);
}

const ByteSet Mnemonic::get_seed(const string& pwd) const
{
    IntByteSet the_seed(0, 64);
    if (is_valid())
    {
        const string pass = get_word_list();
        char salt[8 + pwd.size()];
        strcpy(salt, "mnemonic");
        strcat(salt, pwd.c_str()); // salt = "mnemonic" + password

        // Cf https://www.openssl.org/docs/manmaster/man3/PKCS5_PBKDF2_HMAC.html

        PKCS5_PBKDF2_HMAC( pass.c_str(), pass.size(),
                           reinterpret_cast<const unsigned char *>(salt), strlen(reinterpret_cast<const char *>(salt)),
                           2048,
                           EVP_sha512(),
                           64,
                           the_seed );

        //cout << "BIP32 password : " << pwd.c_str() << endl;
        //cout << "BIP32 seed (hex): " << the_seed << dec << endl;
    }
    return the_seed;
}

//-----------------------------------------------------------------------------------------------------------------

DerivationPath::DerivationPath(string path)
    : m_account_depth(0)
{
    vector<string> p = split(path, "/");
    assert(p.size()>0);
    if(p.size()>1)
    {
        assert(p[0] == "m");
        m_path.push_back(0);            // convention as root key value
        for(int i=1; i<p.size(); i++)
        {
            bool hardened = false;
            string index = p[i];
            uint32_t value = 0;
            if(index.size()>1 && !strcmp(&index.back(),"'"))
            {
                value = 0x80000000;
                index = index.substr(0, index.size()-1);
            }
            if(!strcmp(index.c_str(), "x"))     // value = 0 for x (convention)
            {
                assert(m_account_depth == 0);
                m_account_depth = i;
            }
            else
            {
                uint32_t v = stoi(index.c_str());
                assert(v < 0x80000000);
                value += v;
            }
            m_path.push_back(value);
        }
    }
}

Privkey DerivationPath::deriveRootKey(const Privkey& root_key, const int32_t account_i) const
{
    Privkey x(root_key);
    for(uint8_t i=1;i<m_path.size();i++)
    {
        uint32_t index = (m_path[i] < 0x80000000 ? m_path[i] : m_path[i]-0x80000000) + (i == m_account_depth ? account_i : 0);
        bool hardened = (m_path[i] >= 0x80000000);
        x = Privkey(x, index, hardened);
    }
    return x;
}