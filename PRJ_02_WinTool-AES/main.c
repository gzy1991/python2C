/*  
*   Byte-oriented AES-256 implementation.
*   All lookup tables replaced with 'on the fly' calculations. 
*
*   Copyright (c) 2007 Ilya O. Levin, http://www.literatecode.com
*
*   Permission to use, copy, modify, and distribute this software for any
*   purpose with or without fee is hereby granted, provided that the above
*   copyright notice and this permission notice appear in all copies.
*
*   THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
*   WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
*   MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
*   ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
*   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
*   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
*   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
#include <stdlib.h>
#include <stdio.h>
#include "aes256.h"

#define MAX			10000 
#define MAXLEN		128
#define KEY_LEN		128

#define DUMP(s, i, buf, sz)  {  printf(s);                  \
                              for (i = 0; i < (sz);i++)    \
                                  printf("%02x ", buf[i]); \
                              printf("\n");\
							 }

int main (int argc, char *argv[])
{
	FILE * outfile, *infile,*keyfile,*infile2;
	char ch;
	int error=0;
    aes256_context ctx; 
	uint8_t infile2_name[64]={0};
    uint8_t key[KEY_LEN];
    uint8_t buf[KEY_LEN], i=0;
	uint8_t buf2[KEY_LEN];
	int a,rc, rc2; 
		
	if( argc < 3 )
    {
        printf("usage: %s %s/n", argv[0], "infile outfile");
        exit(1);
    }
   
    
    outfile = fopen(argv[2], "wb" );
    infile = fopen(argv[1], "rb");
	
   
	if( outfile == NULL || infile == NULL )
    {
        printf("%s, %s",argv[1],"not exit/n");
        exit(1);
    }

		
	//==================================================================//
	//   1. 读取密码文件 
	//==================================================================//
	printf("1. 读取密码文件 \r\n");
	keyfile = fopen(argv[3], "rb" );
	if( keyfile == NULL )
    {
        printf("%s, %s",argv[3],"not exist/n");
        exit(1);
    }
	fread( key, sizeof( unsigned char ), KEY_LEN, keyfile );
	fclose(keyfile);

    DUMP("key: ", i, key, sizeof(key));
 
	ch=getchar();	
	//==================================================================//
	//   2. 加密数据块，并写入输出文件
	//==================================================================//
	printf("2. 加密数据块，并写入输出文件 \r\n");

	aes256_init(&ctx, key);
	memset(buf,0,KEY_LEN);

    while( (rc = fread(buf,sizeof(unsigned char), KEY_LEN,infile)) != 0 )
    {
		DUMP("2-0明文: ", i, buf, sizeof(buf));
		if(rc==KEY_LEN)
		{
			aes256_encrypt_ecb(&ctx, buf);
			fwrite( buf, sizeof( unsigned char ), rc, outfile );
			DUMP("2-1密文: ", i, buf, sizeof(buf));
		}
		else
		{
			aes256_encrypt_ecb(&ctx, buf);
			fwrite( buf, sizeof( unsigned char ), KEY_LEN, outfile );
			DUMP("2-2密文: ", i, buf, sizeof(buf));
		}
		memset(buf,0,KEY_LEN);
	} 
	aes256_done(&ctx);
	fclose(outfile);
	fclose(infile);

	ch=getchar();
	//==================================================================//
	//   3.再次读取密码文件，
	//==================================================================//
	printf(" 再次读取密码文件 \r\n");
	keyfile = NULL;
	keyfile = fopen(argv[3], "rb" );
	if( keyfile == NULL )
    {
        printf("%s, %s","KEY.txt","not exist/n");
        exit(1);
    }

	rc = fread(key,sizeof(unsigned char), KEY_LEN,keyfile);
	if(rc!=KEY_LEN)
	{
		printf("Keyfile read Error!\r\n");
	}
	fclose(keyfile);

	DUMP("key: ", i, key, sizeof(key));
	ch=getchar();	
	//==================================================================//
	//   4.解密输出的加密文件---->infile2_name
	//==================================================================//
	printf("4. 打开解密输出的加密文件 \r\n");

	memset(buf,0,KEY_LEN);

	aes256_init(&ctx, key);
	   
	sprintf((char*)infile2_name,"%s_%s","Dec_",argv[1]);
		
	infile2 = fopen((char*)infile2_name, "wb" );
	if( infile2 == NULL )
    {
        printf("%s, %s",infile2_name,"not exit/n");
        exit(1);
    }
	outfile = fopen(argv[2], "rb" );
	if( infile2 == NULL )
    {
        printf("%s, %s",infile2_name,"not exit/n");
        exit(1);
    }
	//==================================================================//
	//    5. 再次解密输出文件-->
	//==================================================================//
	printf("5. 再次解密输出文件 \r\n");

	memset(buf,0,KEY_LEN);
	while( (rc = fread(buf,sizeof(unsigned char), KEY_LEN,outfile)) != 0 )
   {
		DUMP("5-0密文: ", i, buf, sizeof(buf));
		if(rc==KEY_LEN)
		{
			aes256_decrypt_ecb(&ctx, buf);
			DUMP("5-1明文: ", i, buf, sizeof(buf));
			fwrite( buf, sizeof( unsigned char ), rc, infile2 );
		}
		else
		{
			aes256_decrypt_ecb(&ctx, buf);
			DUMP("5-2明文: ", i, buf, sizeof(buf));
			fwrite( buf, sizeof( unsigned char ), KEY_LEN, infile2 );
		}
		memset(buf,0,KEY_LEN);
	} 
    aes256_done(&ctx);
	fclose(outfile);
	fclose(infile2);

	//==================================================================//
	//   compare with the original file
	//==================================================================//
	printf("6. 比较解密输出文件和原文件 \r\n");
	infile2 = fopen((char*)infile2_name, "rb" );
	if( infile2 == NULL )
    {
        printf("%s, %s",infile2_name,"not exit/n");
        exit(1);
    }

	infile = fopen(argv[1], "rb" );
	if( infile == NULL )
    {
        printf("%s, %s",argv[1],"not exit/n");
        exit(1);
    }

	error=0;
    while( (rc = fread(buf,sizeof(unsigned char), KEY_LEN,infile)) != 0&&(rc2 = fread(buf2,sizeof(unsigned char), KEY_LEN,infile2))!=0 )
    {
		for(i=0;i<KEY_LEN;i++)
		{
			if(buf[i]!=buf2[i])
			{
				error++;
				break;
			}
		}
	} 
	if(error>0)
		printf("They are not the same!");
	else
		printf("They are the same!");
		
	fclose(infile);
	fclose(infile2);
    return 0;
} /* main */
