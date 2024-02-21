/******************************************************************************
 * BIKE -- Bit Flipping Key Encapsulation
 *
 * Copyright (c) 2017 Nir Drucker, Shay Gueron, Rafael Misoczki
 * (drucker.nir@gmail.com, shay.gueron@gmail.com, rafaelmisoczki@google.com)
 *
 * Permission to use this code for BIKE is granted.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 *
 * * The names of the contributors may not be used to endorse or promote
 *   products derived from this software without specific prior written
 *   permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHORS ""AS IS"" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS CORPORATION OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************/

#include <iostream>

#include "stdio.h"
#include "kem.h"
#include "utilities.h"
#include "measurements.h"
#include "ntl.h"
#include "conversions.h"


////////////////////////////////////////////////////////////////
//                 Main function for testing
////////////////////////////////////////////////////////////////
int main(void)
{
    /*sk_t sk    = {0}; // private-key: (h0, h1)
    pk_t pk    = {0}; // public-key:  (g0, g1)
    ct_t ct    = {0}; // ciphertext:  (c0, c1)
    ss_t k_enc = {0}; // shared secret after encapsulate
    ss_t k_dec = {0}; // shared secret after decapsulate

    MSG("BIKE Demo Test:\n");

    for (uint32_t i=1; i <= NUM_OF_CODE_TESTS; ++i)
    {
        status_t res = SUCCESS;

        MSG("r: %d Code test: %d \n", (int) R_BITS, i);
        //Key generation.
        MEASURE("  keygen", res = static_cast<status_t>(crypto_kem_keypair(pk.raw, sk.raw)););

        if(res != SUCCESS)
        {
            MSG("Keypair failed with error: %d\n", res);
            continue;
        }

        for (uint32_t j=1; j <= NUM_OF_ENCRYPTION_TESTS; ++j)
        {
            //MSG("Enc/Dec test: %d\n", j);
            uint32_t dec_rc = 0;

            //Encapsulate
            MEASURE("  encaps", res = static_cast<status_t>(crypto_kem_enc(ct.raw, k_enc.raw, pk.raw)););

            if(res != SUCCESS)
            {
                MSG("encapsulate failed with error: %d\n", res);
                continue;
            }

            //Decapsulate
            MEASURE("  decaps", dec_rc = crypto_kem_dec(k_dec.raw, ct.raw, sk.raw););

            if (dec_rc != 0)
            {
                MSG("Decoding failed after %d code tests and %d enc/dec tests!\n", i, j);
            }
            else
            {
                if (safe_cmp(k_enc.raw, k_dec.raw, sizeof(k_dec)/sizeof(uint64_t)))
                {
                    MSG("Success! decapsulated key is the same as encapsulated key!\n");
                } else {
                    MSG("Failure! decapsulated key is NOT the same as encapsulated key!\n");
                }
            }

            DMSG("Initiator's generated key (K) of 256 bits = ");
            print((uint64_t*)k_enc.raw, ELL_SIZE*8);
            DMSG("Responder's computed key (K) of 256 bits  = ");
            print((uint64_t*)k_dec.raw, ELL_SIZE*8);
        }
    }*/


    // 私钥
    sk_t sk = {0}; // private-key: (h0, h1)
    // 公钥
    pk_t pk = {0}; // public-key:  (g0, g1)
    // 密文 在BIKE-PKE中，主要使用c0
    ct_t ct = {0}; // ciphertext:  (c0, c1)
    // 明文（字节表示）
    uint8_t m[ELL_SIZE] = {1,2,3};
    // 明文转换后的向量e
    uint8_t e[N_SIZE] = {0};
    // 解密出的向量e
    uint8_t e_dec[N_SIZE] = {0};

    // BIKE-PKE
    // Step1 明文转换为e
    // 探讨变化明文，可修改m，也可直接修改e
    functionH(e, m);
    // Step2 密钥生成
    crypto_pke_keygen(pk.raw, sk.raw);
    // Step3 加密
    crypto_pke_enc(ct.raw, e, pk.raw);
    // Step4 解密
    crypto_pke_dec(e_dec, ct.raw, sk.raw);

    // 以下为调试使用
    uint8_t e0[R_SIZE] = {0};
    uint8_t e1[R_SIZE] = {0};
    uint8_t e0_dec[R_SIZE] = {0};
    uint8_t e1_dec[R_SIZE] = {0};
    ntl_split_polynomial(e0, e1, e);
    ntl_split_polynomial(e0_dec, e1_dec, e_dec);
    // 各个参数的1的位置信息
    // 私钥
    std::vector<uint32_t> h0_compact;
    std::vector<uint32_t> h1_compact;
    convert2compact_flex(h0_compact, sk.val0, R_SIZE, R_BITS);
    convert2compact_flex(h1_compact, sk.val1, R_SIZE, R_BITS);
    std::cout << "sk-h0, total weight: " << h0_compact.size() << std::endl;
    for(auto pos : h0_compact) {
        std::cout << pos << " ";
    }
    std::cout << std::endl;
    std::cout << "sk-h1, total weight: " << h1_compact.size() << std::endl;
    for(auto pos : h1_compact) {
        std::cout << pos << " ";
    }
    std::cout << std::endl;
    // 公钥
    std::vector<uint32_t> h_compact;
    convert2compact_flex(h_compact, pk.val, R_SIZE, R_BITS);
    std::cout << "pk-h, total weight: " << h_compact.size() << std::endl;
    for(auto pos : h_compact) {
        std::cout << pos << " ";
    }
    std::cout << std::endl;
    // 明文转换后的向量e
    std::vector<uint32_t> e0_compact;
    std::vector<uint32_t> e1_compact;
    convert2compact_flex(e0_compact, e0, R_SIZE, R_BITS);
    convert2compact_flex(e1_compact, e1, R_SIZE, R_BITS);
    std::cout << "e0, total weight: " << e0_compact.size() << std::endl;
    for(auto pos : e0_compact) {
        std::cout << pos << " ";
    }
    std::cout << std::endl;
    std::cout << "e1, total weight: " << e1_compact.size() << std::endl;
    for(auto pos : e1_compact) {
        std::cout << pos << " ";
    }
    std::cout << std::endl;
    // 密文
    std::vector<uint32_t> c0_compact;
    convert2compact_flex(c0_compact, ct.val0, R_SIZE, R_BITS);
    std::cout << "ct-c0, total weight: " << c0_compact.size() << std::endl;
    for(auto pos : c0_compact) {
        std::cout << pos << " ";
    }
    std::cout << std::endl;

    // 比较加密信息与解密信息是否一致
    if(safe_cmp(e, e_dec, N_SIZE))
    {
        printf("Success\n");
    } else {
        printf("Fail\n");
    }

    return 0;
}
