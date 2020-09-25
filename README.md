# yd_crypto

## 最新版本：V1.1.01

***

### 1、文件简介

> 演示(demo)
>> aes_demo.c---AES各种加密模式示例
>>
>> des_demo.c---DES各种加密模式示例
>>
>> tdes_demo.c---TDES各种加密模式示例
>>
>> md5_demo.c---MD5示例
>>
>> sha_demo.c---HASH系列示例
>>
>> sm3_demo.c---国密SM3示例
>>
> 源代码(src)
>> yd_aes_base.c---AES算法核心
>>
>> yd_aes_cbc.c---AES-CBC模式加解密API
>>
>> yd_aes_cbc_cs.c---AES-CBC-CS模式三种变体加解密API
>>
>> yd_aes_cfb.c---AES-CFB模式及不同位数加解密API
>>
>> yd_aes_ecb.c---AES-ECB模式加解密API
>>
>> yd_aes_ofb.c---AES-OFB模式加(解)密API
>>
>> yd_des_base.c---DES算法核心
>>
>> yd_des_cbc.c---DES-CBC模式加解密API
>>
>> yd_des_cfb.c---DES-CFB模式及不同位数加解密API
>>
>> yd_des_ecb.c---DES-ECB模式加解密API
>>
>> yd_des_ofb.c---DES-OFB模式及不同位数加(解)密API
>>
>> yd_tdes_cbc.c---TDES-CBC模式加解密API
>>
>> yd_tdes_cfb.c---TDES-CFB模式及不同位数加解密API
>>
>> yd_tdes_ecb.c---TDES-ECB模式加解密API
>>
>> yd_tdes_ofb.c---TDES-OFB模式加(解)密API
>>
>> yd_md5.c---MD5算法核心及API
>>
>> yd_sha1.c---SHA1算法核心及API
>>
>> yd_sha224.c---SHA224算法核心及API
>>
>> yd_sha256.c---SHA256算法核心及API
>>
>> yd_sm3.c---国密SM3算法核心及API

### 2、更新记录

> 2020-4-11
>> 第一次发布
>>
> 2020-6-29
>> 加入国密SM3算法及示例
>>
> 2020-8-27
>> 注释更新为UTF8编码
>>
> 2020-9-3
>> 修改MD5、SHA、SM3中的全局变量，解决多任务同时调用需要互斥的问题
>>
> 2020-9-17
>> 增加AES CBC-CS三种变体算法及示例，可以加密任意长度字节，不需要是
>>
>> 16字节的整数倍。
