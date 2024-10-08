#include <gtest/gtest.h>
#include <crypto/bips.h>

TEST(SignatureTests, Micah_verify_vectors)
{
    //https://github.com/Zoltu/ethereum-crypto/blob/master/tests/source/index.ts

    const char *message = "hello";
    ByteSet t_raw(message);
    ByteSet t_h(t_raw.keccak256());

    Privkey x(ByteSet("1", 32, 16));
    Signature sig( ByteSet("433EC3D37E4F1253DF15E2DEA412FED8E915737730F74B3DFB1353268F932EF5", 32, 16),
                   ByteSet("557C9158E0B34BCE39DE28D11797B42E9B1ACB2749230885FE075AEDC3E491A4", 32, 16),
                   false );
                                  
    bool expected = true;
    bool actual = sig.isValid(t_h, x.getPubKey().getAddress());
    ASSERT_EQ(actual, expected);

    x = ByteSet("0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364140", 32, 16);
    sig = Signature( ByteSet("45CEA25D72DB4929DC27BC66527BBB215D20E323FF0DE944640930BE5C38C534", 32, 16),
                     ByteSet("34F8904BDE08FB97BE5D01C6BC5AF0189FD76E0E03693E56DAB28BFCD956F150", 32, 16),
                     true );
    expected = true;
    actual = sig.isValid(t_h, x.getPubKey().getAddress());
    ASSERT_EQ(actual, expected);

    x = ByteSet("1", 32, 16);
    sig = Signature( ByteSet("1", 32, 16),
                     ByteSet("1", 32, 16),
                     true );
    expected = false;
    actual = sig.isValid(t_h, x.getPubKey().getAddress());
    ASSERT_EQ(actual, expected);

    x = ByteSet("1", 32, 16);
    sig = Signature( ByteSet("1", 32, 16),
                     ByteSet("1", 32, 16),
                     false );
    expected = false;
    actual = sig.isValid(t_h, x.getPubKey().getAddress());
    ASSERT_EQ(actual, expected);
}

TEST(SignatureTests, Micah_recover_vectors)
{
    //https://github.com/Zoltu/ethereum-crypto/blob/master/tests/source/index.ts

    Pubkey k;
    const char *message = "hello";
    ByteSet t_raw(message);
    ByteSet t_h(t_raw.keccak256());

    Privkey x(ByteSet("1", 32, 16));
    Signature sig = x.sign(t_h);
    sig.ecrecover(k, t_h);                                  
    Point expected = x.getPubKey().getPoint();
    Point actual = k.getPoint();
    ASSERT_EQ(actual, expected);

    x = ByteSet("0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364140", 32, 16);
    sig = x.sign(t_h);
    sig.ecrecover(k, t_h);  
    expected = x.getPubKey().getPoint();
    actual = k.getPoint();
    ASSERT_EQ(actual, expected);
}

TEST(SignatureTests, test_boundaries)
{
    //Small field curve for edge-case testing purposes
    Integer p = 211;
    Point G(12,70);
    Integer n = 199;
    EllipticCurve ecc = EllipticCurve(p, 0, 7, G, n);

    Integer x_candidate = 24;
    Privkey x(ByteSet(x_candidate, 1), ecc);
    Pubkey Q;

    const char *msg = "hello";
    ByteSet msg_raw(msg);
    ByteSet msg_h(msg_raw.keccak256());
    
    //pre EIP-2 signature:
    // k = 69
    // R = (202, 79)
    // r = R.x mod 199 = 3
    // s = 102                  => EIP-2 incompatible
    // R.y % 2 = true
    Signature sig = Signature(3, 102, true, ecc);
    //pre EIP-2
    auto expected = true;
    auto actual = sig.isValid(msg_h, x.getPubKey().getAddress(), false);
    ASSERT_EQ(actual, expected);
    //post EIP-2
    expected = false;
    actual = sig.isValid(msg_h, x.getPubKey().getAddress(), true);
    ASSERT_EQ(actual, expected);

    //post EIP-2 signature:
    // k = 69
    // R' = -R = (202, 132)
    // r = R'.x mod 199 = 3
    // s' = -s = 97             => EIP-2 compatible
    // R'.y % 2 = false
    sig = Signature(3, 97, false, ecc);
    //pre EIP-2
    expected = true;
    actual = sig.isValid(msg_h, x.getPubKey().getAddress(), false);
    ASSERT_EQ(actual, expected);
    //post EIP-2
    expected = true;
    actual = sig.isValid(msg_h, x.getPubKey().getAddress(), true);
    ASSERT_EQ(actual, expected);
}