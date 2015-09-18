//
//  main.c
//  read_join
//
//  Created by steven on 2/9/15.
//  Copyright (c) 2015 yandell lab. All rights reserved.
//

#include <stdio.h>
#include "kseq.h"
#include <zlib.h>

KSEQ_INIT(gzFile, gzread)

int main(int argc, const char * argv[]) {
    
    if (argc < 4) {
        
        FILE * out = fopen(argv[2], "w");
        
        kseq_t * seq1;
        gzFile * fp1 = gzopen(argv[1], "r");
        seq1 = kseq_init(fp1);
        
        int l1;
        uint64_t line_count = 1;
        l1 = kseq_read(seq1);
        char tmp[2000];
        memset(tmp, '\0', sizeof(char)*2000);
        
        while (l1 >= 0) {
            if (line_count % 2 == 0) {
                fprintf(out, ">%s\n%sN%s\n",seq1->name.s, seq1->seq.s, tmp);
                //printf("name of read output: %s\n",seq1->name.s);
            }
            else {
                memset(tmp, '\0', sizeof(char)*2000);
                sprintf(tmp, "%s",seq1->seq.s);
                //printf("name of read saved: %s\n",seq1->name.s);
            }
            
            line_count++;
            l1 = kseq_read(seq1);
        }
        
        kseq_destroy(seq1);
        gzclose(fp1);

    }
    
    else {
    
        FILE * out = fopen(argv[3], "w");
        
        kseq_t * seq1;
        kseq_t * seq2;
        
        gzFile * fp1 = gzopen(argv[1], "r");
        gzFile * fp2 = gzopen(argv[2], "r");
        
        
        seq1 = kseq_init(fp1);
        seq2 = kseq_init(fp2);
        
        int l1,l2;
        l1 = kseq_read(seq1);
        l2 = kseq_read(seq2);
        while (l1 >= 0 && l2 >= 0) {
            /*if (strncmp(seq1->name.s, seq2->name.s, seq1->seq.l) != 0) {
                printf("problem, names of reads not the same\n");
                printf("%s\n%s\n",seq1->name.s,seq2->name.s);
            }*/
            //else {
            char tmp[2000];
            memset(tmp, '\0', sizeof(char)*2000);
            sprintf(tmp, "%sN%s",seq1->seq.s,seq2->seq.s);
            fprintf(out, ">%s\n%s\n",seq1->name.s,tmp);
            //}
            l1 = kseq_read(seq1);
            l2 = kseq_read(seq2);
        }
        
        kseq_destroy(seq1);
        kseq_destroy(seq2);
        gzclose(fp1);
        gzclose(fp2);
    
    }
    
    return 0;
}
