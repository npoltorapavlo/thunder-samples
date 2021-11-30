#pragma once

#include "Module.h"

#ifdef ENABLE_SECAPI
#include "token.h"
#endif

#include <memory>

class JWTFactory {
private:
  JWTFactory(const JWTFactory &) = delete;
  JWTFactory &operator=(const JWTFactory &) = delete;
  JWTFactory() {
    #ifndef ENABLE_SECAPI
    for (uint8_t index = 0; index < sizeof(_secretKey); index++) {
      WPEFramework::Crypto::Random(_secretKey[index]);
    }
    #endif
  }

public:
  static JWTFactory &Instance() {
    static JWTFactory _instance;
    return (_instance);
  }

  #ifdef ENABLE_SECAPI
  typedef JWTSecApi ELEMENT;
  #else
  typedef WPEFramework::Web::JSONWebToken ELEMENT;
  #endif

  inline std::unique_ptr<ELEMENT> Element() {
    return std::unique_ptr<ELEMENT>(new ELEMENT
        #ifndef ENABLE_SECAPI
        (WPEFramework::Web::JSONWebToken::SHA256, sizeof(_secretKey), _secretKey)
        #endif
        );
  }

private:
  #ifndef ENABLE_SECAPI
  uint8_t _secretKey[WPEFramework::Crypto::SHA256::Length];
  #endif
};
