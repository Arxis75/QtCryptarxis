#pragma once

#include <crypto/bips.h>
#include <data/RLPByteSet.h>
#include <data/HexStrByteSet.h>

class AccessList
{
    public:
        AccessList(const RLPByteSet& raw_access_list) : m_rlp_accessList(raw_access_list) {};

        //TODO const ByteSet& getAddress(const ByteSet& key) const;
        //TODO const vector<ByteSet>& getKeys(const ByteSet& address) const;
        //TODO const bool hasAddress(ByteSet& address) const;
        //TODO const bool hasKey(ByteSet& key) const;

        const RLPByteSet serialize() const { return m_rlp_accessList; }

    protected:
        //TODO void addKey(const ByteSet& address, const ByteSet& key) {};
        //TODO void removeKey(const ByteSet& address, const ByteSet& key) {};

    private:
        RLPByteSet m_rlp_accessList;
        //TODO map<ByteSet, vector<ByteSet>> m_accessList;
};

class TransactionPayload
{
    public:
        enum class Format{PRE_EIP_155 = -1, EIP_155 = 0, EIP_2930 = 1, EIP_1559 = 2};
    
        ///
        /// @brief Construct a new PRE_EIP_155 Transaction object
        ///
        ///
        TransactionPayload(
            const HexStrByteSet& nonce,
            const HexStrByteSet& gasPrice,
            const HexStrByteSet& gasLimit,
            const HexStrByteSet& to,
            const HexStrByteSet& value,
            const HexStrByteSet& data);

        ///
        /// @brief Construct a new EIP155 Transaction object
        /// 
        ///
        TransactionPayload(
            const HexStrByteSet& chainId,
            const HexStrByteSet& nonce,
            const HexStrByteSet& gasPrice,
            const HexStrByteSet& gasLimit,
            const HexStrByteSet& to,
            const HexStrByteSet& value,
            const HexStrByteSet& data
            );

        ///
        /// @brief Construct a new EIP_2930 Transaction object
        /// 
        ///
         TransactionPayload(
            const HexStrByteSet& chainId,
            const HexStrByteSet& nonce,
            const HexStrByteSet& gasPrice,
            const HexStrByteSet& gasLimit,
            const HexStrByteSet& to,
            const HexStrByteSet& value,
            const HexStrByteSet& data,
            const AccessList& accessList
            );

        ///
        /// @brief Construct a new EIP_1559 Transaction object
        /// 
        ///
         TransactionPayload(
            const HexStrByteSet& chainId,
            const HexStrByteSet& nonce,
            const HexStrByteSet& max_priority_fee_per_gas,
            const HexStrByteSet& max_fee_per_gas,
            const HexStrByteSet& gasLimit,
            const HexStrByteSet& to,
            const HexStrByteSet& value,
            const HexStrByteSet& data,
            const AccessList& accessList
            );

        const RLPByteSet serialize() const;
        const RLPByteSet serializeAsSigningPayload() const;

        const Format getFormat() const { return m_format; }
        const HexStrByteSet& getChainId() const { return m_chainId; }
        const HexStrByteSet& getNonce() const { return m_nonce; }
        const HexStrByteSet& getGasPrice() const { return m_gasPrice; }
        const HexStrByteSet& getGasLimit() const { return m_gasLimit; }
        const HexStrByteSet& getMaxPriorityFeePerGas() const { return m_max_priority_fee_per_gas; }
        const HexStrByteSet& getMaxFeePerGas() const { return m_max_fee_per_gas; }
        const HexStrByteSet& getTo() const { return m_to; }
        const HexStrByteSet& getValue() const { return m_value; }
        const HexStrByteSet& getData() const { return m_data; }
        const AccessList& getAccessList() const { return m_accessList; }

    private:
        const Format m_format;
        const HexStrByteSet m_chainId;
        const HexStrByteSet m_nonce;
        const HexStrByteSet m_gasPrice;
        const HexStrByteSet m_max_priority_fee_per_gas;
        const HexStrByteSet m_max_fee_per_gas;
        const HexStrByteSet m_gasLimit;
        const HexStrByteSet m_to;
        const HexStrByteSet m_value;
        const HexStrByteSet m_data;
        const AccessList m_accessList;
};

class SignedTransaction
{
    public:
        /// @brief Constructor for signing an unsigned transaction with a private key
        /// @param unsigned_transaction 
        /// @param secret 
        SignedTransaction(const TransactionPayload& unsigned_transaction, const Privkey& secret);

        /// @brief Constructor from an unsigned transaction and a signature
        /// @param unsigned_transaction 
        /// @param sig 
        SignedTransaction(const TransactionPayload& unsigned_transaction, const Signature& sig);

        const RLPByteSet serialize() const;

        /// @brief Creates a new SignedTransaction object from a raw rlp if the structure matches
        /// @param raw_rlp
        static SignedTransaction* parse(const string& raw_tx);

        const TransactionPayload& getPayload() const { return m_payload; }
        const Signature& getSignature() const { return m_signature; }

    private:
        TransactionPayload m_payload;
        Signature m_signature;
};
