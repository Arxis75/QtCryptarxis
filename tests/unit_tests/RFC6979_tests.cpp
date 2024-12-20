#include <gtest/gtest.h>
#include <crypto/bips.h>
#include <data/ByteSet.h>

TEST(RFC6979Tests, RFC6979_NIST_P256)
{
    EllipticCurve ecc = Secp256r1::GetInstance();
    Privkey x(StrByteSet<Hex>("0xC9AFA9D845BA75166B5C215767B1D6934E50C3DB36E89B127B8A622B120F6721", 32), ecc);
    Pubkey U = x.getPubKey();
    
    Integer expected = StrByteSet<Hex>("60FED4BA255A9D31C961EB74C6356D68C049B8923B61FA6CE669622E60F29FB6", 32);
    Integer actual = U.getPoint().getX();
    ASSERT_EQ(actual, expected);
    expected = StrByteSet<Hex>("7903FE1008B8BC99A41AE9E95628BC64F2F1B20C2D7E9F5177A3C294D4462299", 32);
    actual = U.getPoint().getY();
    ASSERT_EQ(actual, expected);

    const char *message = "sample";
    RawByteSet t_raw(message);
    ByteSet t_h(t_raw.sha256());

    expected = StrByteSet<Hex>("A6E3C57DD01ABE90086538398355DD4C3B17AA873382B0F24D6129493D8AAD60", 32);
    actual = ecc.generate_RFC6979_nonce(x.getSecret(), t_h, 0);
    ASSERT_EQ(actual, expected);

    Signature expected_signature( StrByteSet<Hex>("EFD48B2AACB6A8FD1140DD9CD45E81D69D2C877B56AAF991C34D0EA84EAF3716", 32),
                                  StrByteSet<Hex>("F7CB1C942D657C41D436C7A1B6E29F65F3E900DBB9AFF4064DC4AB2F843ACDA8", 32),
                                  false );
    Signature actual_signature = x.sign(t_h, false);    //false = malleability fix not enforced by default in the RFC6979
    
    expected = expected_signature.get_imparity();
    actual = actual_signature.get_imparity();
    ASSERT_EQ(actual, expected);
    expected = expected_signature.get_r();
    actual = actual_signature.get_r();
    ASSERT_EQ(actual, expected);
    expected = expected_signature.get_s();
    actual = actual_signature.get_s();
    ASSERT_EQ(actual, expected);

    message = const_cast<const char*>("test");
    t_raw = RawByteSet(message);
    t_h = ByteSet(t_raw.sha256());

    expected = StrByteSet<Hex>("D16B6AE827F17175E040871A1C7EC3500192C4C92677336EC2537ACAEE0008E0", 32);
    actual = ecc.generate_RFC6979_nonce(x.getSecret(), t_h, 0);
    ASSERT_EQ(actual, expected);

    expected_signature = Signature( StrByteSet<Hex>("F1ABB023518351CD71D881567B1EA663ED3EFCF6C5132B354F28D3B0B7D38367", 32),
                                    StrByteSet<Hex>("019F4113742A2B14BD25926B49C649155F267E60D3814B4C0CC84250E46F0083", 32),
                                    false );
    actual_signature = x.sign(t_h, false);    //false = malleability fix not enforced by default in the RFC

    expected = expected_signature.get_imparity();
    actual = actual_signature.get_imparity();
    ASSERT_EQ(actual, expected);
    expected = expected_signature.get_r();
    actual = actual_signature.get_r();
    ASSERT_EQ(actual, expected);
    expected = expected_signature.get_s();
    actual = actual_signature.get_s();
    ASSERT_EQ(actual, expected);
}

TEST(RFC6979Tests, test_boundaries)
{
    //Small field curve for edge-case testing purposes
    Integer p = 211;
    Point G(12,70);
    Integer n = 199;
    EllipticCurve ecc = EllipticCurve(p, 0, 7, G, n);

    Integer x_candidate = 24;
    Privkey x(ByteSet(x_candidate, 1), ecc);
    Pubkey Q = x.getPubKey();

    const char *msg = "hello";
    RawByteSet msg_raw(msg);
    ByteSet msg_h(msg_raw.keccak256());
    
    Signature expected_sig(188, 44, true, ecc);
    Signature actual_sig = x.sign(msg_h, true);
    // "sign" initiale iteration:
    // k0 = 69
    // R0 = (202, 79)
    // r0 = 202
    // s0 = 102
    // R0.y % 2 = true
    // => Out-of-bound r(=202) forces RFC6979 to iterate
    // k1 = 229
    // => Out-of-bound k(=229) forces RFC6979 to re-iterate
    // "sign" final iteration:
    // k2 = 89
    // R2 = (188, 17)
    // r2 = 188
    // s2 = 44
    // R2.y % 2 = true
    ASSERT_EQ(actual_sig, expected_sig);

    Pubkey Q_candidate;
    actual_sig.ecrecover(Q_candidate, msg_h, x.getPubKey().getAddress());
    auto expected = true;
    auto actual = (Q_candidate == Q);
    ASSERT_EQ(actual, expected);
}

TEST(RFC6979Tests, Micah_sign_vectors)
{
    const char *message = "hello";
    RawByteSet t_raw(message);
    ByteSet t_h(t_raw.keccak256());

    Privkey x(StrByteSet<Hex>("1", 32));
    Signature expected_signature( StrByteSet<Hex>("433EC3D37E4F1253DF15E2DEA412FED8E915737730F74B3DFB1353268F932EF5", 32),
                                  StrByteSet<Hex>("557C9158E0B34BCE39DE28D11797B42E9B1ACB2749230885FE075AEDC3E491A4", 32),
                                  false );
    Signature actual_signature = x.sign(t_h);
    Integer expected = expected_signature.get_imparity();
    Integer actual = actual_signature.get_imparity();
    ASSERT_EQ(actual, expected);
    expected = expected_signature.get_r();
    actual = actual_signature.get_r();
    ASSERT_EQ(actual, expected);
    expected = expected_signature.get_s();
    actual = actual_signature.get_s();
    ASSERT_EQ(actual, expected);

    x = StrByteSet<Hex>("0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364140", 32);
    expected_signature = Signature( StrByteSet<Hex>("45CEA25D72DB4929DC27BC66527BBB215D20E323FF0DE944640930BE5C38C534", 32),
                                    StrByteSet<Hex>("34F8904BDE08FB97BE5D01C6BC5AF0189FD76E0E03693E56DAB28BFCD956F150", 32),
                                    true );
    actual_signature = x.sign(t_h);
    expected = expected_signature.get_imparity();
    actual = actual_signature.get_imparity();
    ASSERT_EQ(actual, expected);
    expected = expected_signature.get_r();
    actual = actual_signature.get_r();
    ASSERT_EQ(actual, expected);
    expected = expected_signature.get_s();
    actual = actual_signature.get_s();
    ASSERT_EQ(actual, expected);
}