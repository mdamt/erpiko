#ifndef _CIPHER_H
#define _CIPHER_H

#include "erpiko/oid.h"
#include <vector>

namespace Erpiko {

namespace CipherConstants {
  enum Mode {
    DECRYPT = 0,
    ENCRYPT = 1
  };

  const char* const AES_128_ECB = "2.16.840.1.101.3.4.1.1";
  const char* const AES_128_CBC = "2.16.840.1.101.3.4.1.2";
  const char* const AES_128_OFB = "2.16.840.1.101.3.4.1.3";
  const char* const AES_128_CFB = "2.16.840.1.101.3.4.1.4";
  const char* const AES_128_GCM = "2.16.840.1.101.3.4.1.6";
  const char* const AES_192_ECB = "2.16.840.1.101.3.4.1.21";
  const char* const AES_192_CBC = "2.16.840.1.101.3.4.1.22";
  const char* const AES_192_OFB = "2.16.840.1.101.3.4.1.23";
  const char* const AES_192_CFB = "2.16.840.1.101.3.4.1.24";
  const char* const AES_192_GCM = "2.16.840.1.101.3.4.1.26";
  const char* const AES_256_ECB = "2.16.840.1.101.3.4.1.41";
  const char* const AES_256_CBC = "2.16.840.1.101.3.4.1.42";
  const char* const AES_256_OFB = "2.16.840.1.101.3.4.1.43";
  const char* const AES_256_CFB = "2.16.840.1.101.3.4.1.44";
  const char* const AES_256_GCM = "2.16.840.1.101.3.4.1.46";
  const char* const RC2_CBC = "1.2.840.113549.3.2";
  const char* const RC2_128_CBC = "1.2.840.113549.3.2";
  const char* const RC2_64_CBC = "rc2-64-cbc";
  const char* const RC4_CBC = "1.2.840.113549.3.4";
  const char* const CAST5_128_CBC = "1.2.840.113533.7.66.10";
  const char* const TRIPLEDES_CBC = "des3";
  const char* const DES = "des";

}

/**
 * Cipher interface. This interface should be implemented by cipher implementors.
 */
class Cipher {

  private:
    Cipher();

  public:
    Cipher(CipherConstants::Mode mode, std::vector<unsigned char> key, std::vector<unsigned char> iv);
    virtual ~Cipher();

    static Cipher* get(const ObjectId& algorithmId, CipherConstants::Mode mode, std::vector<unsigned char> key, std::vector<unsigned char> iv);

    /**
     * Adds a new data to be ciphered
     * @param data The data to be ciphered
     * @return the cipher/deciphered data
     */
    virtual std::vector<unsigned char> update(std::vector<unsigned char> data) = 0;

    /**
     * Finalizes a cipher/decipher operation. This is usable when the incoming data size is not the same as the block size, which implies padding.
     * For non-padded data, this will only returns an empty vector.
     * @return the cipher/deciphered data
     */
    virtual std::vector<unsigned char> finalize() = 0;

    /**
     * Sets whether padding should be enabled or not. Default is yes.
     * @param enabled Padding is enabled
     */
    virtual void enablePadding(bool enabled) = 0;

    /**
     * Sets the authentication tag. Default implementation does nothing
     * @param tag authentication tag
     */
    virtual void setTag(std::vector<unsigned char> tag);

    /**
     * Gets the authentication tag. Default implementation returns an empty vector
     * @return authentication tag
     */
    virtual std::vector<unsigned char> getTag();


    /**
     * Sets the additional authentication data. Default implementation does nothing
     * @param tag additional authentication data
     */
    virtual void setAad(std::vector<unsigned char> aad);




};

} // namespace Erpiko
#endif // _CIPHER_H
