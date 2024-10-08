#include <eth/Transaction.h>

TransactionPayload::TransactionPayload(
    const ByteSet& nonce,
    const ByteSet& gasPrice,
    const ByteSet& gasLimit,
    const ByteSet& to,
    const ByteSet& value,
    const ByteSet& data
    )
    : m_format(Format::PRE_EIP_155)
    , m_chainId(Integer::zero)
    , m_nonce(nonce)
    , m_gasPrice(gasPrice)
    , m_max_priority_fee_per_gas(ByteSet())
    , m_max_fee_per_gas(ByteSet())
    , m_gasLimit(gasLimit)
    , m_to(to)
    , m_value(value)
    , m_data(data)
    , m_accessList(RLPByteSet())
    { }

TransactionPayload::TransactionPayload(
    const ByteSet& chainId,
    const ByteSet& nonce,
    const ByteSet& gasPrice,
    const ByteSet& gasLimit,
    const ByteSet& to,
    const ByteSet& value,
    const ByteSet& data
    )
    : m_format(Format::EIP_155)
    , m_chainId(chainId)
    , m_nonce(nonce)
    , m_gasPrice(gasPrice)
    , m_max_priority_fee_per_gas(ByteSet())
    , m_max_fee_per_gas(ByteSet())
    , m_gasLimit(gasLimit)
    , m_to(to)
    , m_value(value)
    , m_data(data)
    , m_accessList(RLPByteSet())
    { }

///
/// @brief Construct a new EIP_2930 Transaction object
/// 
///
TransactionPayload::TransactionPayload(
    const ByteSet& chainId,
    const ByteSet& nonce,
    const ByteSet& gasPrice,
    const ByteSet& gasLimit,
    const ByteSet& to,
    const ByteSet& value,
    const ByteSet& data,
    const AccessList& accessList
    )
    : m_format(Format::EIP_2930)
    , m_chainId(chainId)
    , m_nonce(nonce)
    , m_gasPrice(gasPrice)
    , m_max_priority_fee_per_gas(ByteSet())
    , m_max_fee_per_gas(ByteSet())
    , m_gasLimit(gasLimit)
    , m_to(to)
    , m_value(value)
    , m_data(data)
    , m_accessList(accessList)
    { }
///
/// @brief Construct a new EIP_1559 Transaction object
/// 
///
TransactionPayload::TransactionPayload(
    const ByteSet& chainId,
    const ByteSet& nonce,
    const ByteSet& max_priority_fee_per_gas,
    const ByteSet& max_fee_per_gas,
    const ByteSet& gasLimit,
    const ByteSet& to,
    const ByteSet& value,
    const ByteSet& data,
    const AccessList& accessList
    )
    : m_format(Format::EIP_1559)
    , m_chainId(chainId)
    , m_nonce(nonce)
    , m_gasPrice(ByteSet())
    , m_max_priority_fee_per_gas(max_priority_fee_per_gas)
    , m_max_fee_per_gas(max_fee_per_gas)
    , m_gasLimit(gasLimit)
    , m_to(to)
    , m_value(value)
    , m_data(data)
    , m_accessList(accessList)
    {};

const RLPByteSet TransactionPayload::serialize() const
{
    RLPByteSet payload;

    switch(m_format) {
    case Format::EIP_2930:
    case Format::EIP_1559:
        payload.push_back(m_chainId);
        break;
    }
    payload.push_back(m_nonce);
    switch(m_format) {
        case Format::PRE_EIP_155:
        case Format::EIP_155:
        case Format::EIP_2930:
            payload.push_back(m_gasPrice);
            break;
        case Format::EIP_1559:
            payload.push_back(m_max_priority_fee_per_gas);
            payload.push_back(m_max_fee_per_gas);
            break;
    }
    payload.push_back(m_gasLimit);
    payload.push_back(m_to);
    payload.push_back(m_value);
    payload.push_back(m_data);
    switch(m_format) {
        case Format::EIP_2930:
        case Format::EIP_1559:
            payload.push_back(m_accessList.serialize());
            break;
    }
    return payload;
}

const RLPByteSet TransactionPayload::serializeAsSigningPayload() const
{
    RLPByteSet payload = serialize();
    switch(m_format) {
        case Format::PRE_EIP_155:
            break;
        case Format::EIP_155:
            payload.push_back(m_chainId);
            payload.push_back(ByteSet(), 0);
            payload.push_back(ByteSet(), 0);
            break;
        default:
            payload.ByteSet::push_front((uint64_t)m_format, 1);    // Put the 1-Byte Tx type in front (Cf eip-2718)
            break;
    }
    return payload;
}

//**********************************************************************************************************//

SignedTransaction::SignedTransaction(const TransactionPayload& t, const Privkey& secret)
    : m_payload(t)
    , m_signature(secret.sign(t.serializeAsSigningPayload().keccak256()))
{}  

SignedTransaction::SignedTransaction(const TransactionPayload& t, const Signature& sig)
    : m_payload(t)
    , m_signature(sig)
{} 

const RLPByteSet SignedTransaction::serialize() const
{
    RLPByteSet payload = m_payload.serialize();
    switch(m_payload.getFormat()) {
        case TransactionPayload::Format::PRE_EIP_155:
            payload.push_back(ByteSet((uint64_t)27 + (uint8_t)m_signature.get_imparity()));
            break;
        case TransactionPayload::Format::EIP_155:
            payload.push_back(ByteSet(35 + 2*Integer(m_payload.getChainId()) + m_signature.get_imparity()));
            break;
        default:
            payload.push_back(ByteSet(m_signature.get_imparity()));
            break;
    }
    payload.push_back(ByteSet(m_signature.get_r(), 32));
    payload.push_back(ByteSet(m_signature.get_s(), 32));
    switch(m_payload.getFormat()) {
        case TransactionPayload::Format::PRE_EIP_155:
        case TransactionPayload::Format::EIP_155:
            break;
        default:
            payload.ByteSet::push_front((uint64_t)m_payload.getFormat(), 1);    // Put the 1-Byte Tx type in front
            break;
        }
    return payload;
}

SignedTransaction* SignedTransaction::parse(const string& str_raw_tx)
{
    SignedTransaction* pstx = nullptr;
    AccessList access_list = AccessList(RLPByteSet());
    bool is_list = false;
    ByteSet chainId, nonce, gasPrice, max_priority_fee_per_gas, max_fee_per_gas, gasLimit, to, value, data, r, s;
    Integer v;
    RLPByteSet rlp_to_parse(str_raw_tx.c_str());

    // Makes the assumption that the first byte is the tx type (among {0x01, 0x02}).
    // In case of old tx formats (pre EIP155 & EIP155), this is incorrect, but those old tx usually start
    // with RLP list prefix 0xf.., so we should be fine...
    TransactionPayload::Format tx_type = (TransactionPayload::Format)rlp_to_parse.ByteSet::as_uint8();

    switch(tx_type) {
        case TransactionPayload::Format::EIP_2930:
        case TransactionPayload::Format::EIP_1559:
            rlp_to_parse.pop_front(is_list);                // removes the transaction type
            chainId = rlp_to_parse.pop_front(is_list);
            break;
    }
    nonce = rlp_to_parse.pop_front(is_list);
    switch(tx_type) {
        case TransactionPayload::Format::EIP_1559:
            max_priority_fee_per_gas = rlp_to_parse.pop_front(is_list);
            max_fee_per_gas =  rlp_to_parse.pop_front(is_list);
            break;
        default:
            gasPrice = rlp_to_parse.pop_front(is_list);
            break;
    }
    gasLimit = rlp_to_parse.pop_front(is_list);
    to = rlp_to_parse.pop_front(is_list);
    value = rlp_to_parse.pop_front(is_list);
    data = rlp_to_parse.pop_front(is_list);
    switch(tx_type) {
        case TransactionPayload::Format::EIP_2930:
        case TransactionPayload::Format::EIP_1559:
            access_list = AccessList(rlp_to_parse.pop_front(is_list));
            break;
    }
    v = rlp_to_parse.pop_front(is_list);
    if(v == 27 || v == 28) {
        tx_type =  TransactionPayload::Format::PRE_EIP_155;
        v = (v+1)%2;                                        //converts v to {0,1}
    }
    else if(v >= 37) {
        chainId = (uint64_t)(v-35)/2;                       //Cf EIP 155
        tx_type =  TransactionPayload::Format::EIP_155;
        v = (v+1)%2;                                        //converts v to {0,1}
    }
    r = rlp_to_parse.pop_front(is_list);
    s = rlp_to_parse.pop_front(is_list);

    if(to.byteSize() == 20 && (v == 0 || v == 1) && r.byteSize() == 32 && s.byteSize() == 32) {  //minimal conformity verification
        switch(tx_type) {
            case TransactionPayload::Format::PRE_EIP_155:
                pstx = new SignedTransaction(TransactionPayload(nonce, gasPrice, gasLimit, to, value, data), Signature(r,s,v));
                break;
            case TransactionPayload::Format::EIP_155:
                pstx  = new SignedTransaction(TransactionPayload(chainId, nonce, gasPrice, gasLimit, to, value, data), Signature(r,s,v));
                break;
            case TransactionPayload::Format::EIP_2930:
                pstx  = new SignedTransaction(TransactionPayload(chainId, nonce, gasPrice, gasLimit, to, value, data, access_list), Signature(r,s,v));
                break;
            case TransactionPayload::Format::EIP_1559:
                pstx  = new SignedTransaction(TransactionPayload(chainId, nonce, max_priority_fee_per_gas, max_fee_per_gas, gasLimit, to, value, data, access_list), Signature(r,s,v));
                break;
        }
    }

    return pstx;
}
