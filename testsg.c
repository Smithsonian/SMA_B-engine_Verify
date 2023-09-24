#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vdif_files.h"
#include "vdif_frames.h"

int main(int argc, const char **argv) {
	int ii;
	int num_packets;
	int num_files;
	int packets_read;
	int pkt_size_8byte;
	SGGroup_t group;
	vdif_header_t *pkt1, *pkt2;
	void *buf;

	uint32_t VDIF_seconds;
	uint32_t VDIF_frame_index;
	uint32_t diff_VDIF_frame;
	uint32_t previous_VDIF_frame_index=0;
	uint32_t previous_VDIF_seconds=0;

    int64_t b_engine_tmp = 0;
	int32_t b_engine_clk_0;
	int32_t b_engine_sec_0;
	uint32_t b_engine_Cid_0;
	uint32_t b_engine_Fid_0;
	uint32_t b_engine_Fid_tmp;
	int32_t b_engine_clk_1;
	int32_t b_engine_sec_1;
	uint32_t b_engine_Cid_1;
	uint32_t b_engine_Fid_1;
	int32_t previous_b_engine_clk_0=0;
	int32_t previous_b_engine_sec_0=0;
	int32_t previous_b_engine_Cid_0=0;
	int32_t previous_b_engine_Fid_0=0;
	int32_t previous_b_engine_clk_1=0;
	int32_t previous_b_engine_sec_1=0;
	int32_t previous_b_engine_Cid_1=0;
	int32_t previous_b_engine_Fid_1=0;

//newly added
	int32_t b_engine_clk_error=0;
	int32_t b_engine_sec_error=0;
	int32_t b_engine_Cid_error=0;
	int32_t b_engine_Fid_error=0;



	int32_t diff_Cid_0=0;
	int32_t diff_Cid_1=0;
	int32_t cnt_pkt, cnt_B_engine;	
	int32_t B_engine_pkt_len, VDIF_pkt_len, VTP_len;
	int32_t B_engine_pkt_num_per_VDIF, VTP_num_per_VDIF;
	int32_t ROACH_id_0;
	int32_t ROACH_id_1;

        char *pp = (char*)(argv[2]+1); 

printf("Last ID: %c\n", *(pp-2));
       

      

        char timestamp_filename_0[33];
		char timestamp_jump_filename_0[40];

		char timestamp_filename_1[33];
		char timestamp_jump_filename_1[40];

                char error_id_filename[40];//newly added

		char VDIF_timestamp_filename[30];
		char VDIF_timestamp_jump_filename[40];
		vdif_header_t *pkt3, *pkt4, *B_engine_pkt_0, *B_engine_pkt_1;
        FILE * timestamp_file_0, * timestamp_jump_file_0, * timestamp_file_1, * timestamp_jump_file_1;
		FILE * VDIF_timestamp_file, * VDIF_timestamp_jump_file;
                FILE * Error_ROACH2_id;
    
         ROACH_id_0 = (atoi(&argv[2][11]) - 1)*2;
	 ROACH_id_1 = (atoi(&argv[2][11]) - 1)*2 + 1;

        printf("ROACH ID %d %d\n", ROACH_id_0, ROACH_id_1);
        strcpy(timestamp_filename_0,"B_engine_timestamp_0_");
        strncpy(timestamp_filename_0+21,&argv[2][34],4);
        strcpy(timestamp_filename_0+25,"_");
        strncpy(timestamp_filename_0+26,&argv[2][11],1);
        strcpy(timestamp_filename_0+27,".text");

        
        strcpy(timestamp_jump_filename_0,"B_engine_timestamp_0_jump_");
        strncpy(timestamp_jump_filename_0+26,&argv[2][34],4);
        strcpy(timestamp_jump_filename_0+30,"_");
        strncpy(timestamp_jump_filename_0+31,&argv[2][11],1);
        strcpy(timestamp_jump_filename_0+32,".text");


//newly added
		strcpy(error_id_filename,"B_engine_error_id_");
		strncpy(error_id_filename+18,&argv[2][34],4);
        strcpy(error_id_filename+22,"_");
        strncpy(error_id_filename+23,&argv[2][11],1);
        strcpy(error_id_filename+24,".text");

        printf("B_engine_filename is %s,%s\n",timestamp_filename_0,timestamp_jump_filename_0);

		timestamp_file_0=fopen(timestamp_filename_0,"w");
        timestamp_jump_file_0=fopen(timestamp_jump_filename_0,"w");
       Error_ROACH2_id=fopen(error_id_filename,"w");//newly added
   

		strcpy(timestamp_filename_1,"B_engine_timestamp_1_");
        strncpy(timestamp_filename_1+21,&argv[2][34],4);
        strcpy(timestamp_filename_1+25,"_");
        strncpy(timestamp_filename_1+26,&argv[2][11],1);
        strcpy(timestamp_filename_1+27,".text");

        
        strcpy(timestamp_jump_filename_1,"B_engine_timestamp_1_jump_");
        strncpy(timestamp_jump_filename_1+26,&argv[2][34],4);
        strcpy(timestamp_jump_filename_1+30,"_");
        strncpy(timestamp_jump_filename_1+31,&argv[2][11],1);
        strcpy(timestamp_jump_filename_1+32,".text");

        printf("B_engine_filename is %s,%s\n",timestamp_filename_1,timestamp_jump_filename_1);

		timestamp_file_1=fopen(timestamp_filename_1,"w");
        timestamp_jump_file_1=fopen(timestamp_jump_filename_1,"w");



        strcpy(VDIF_timestamp_filename,"VDIF_timestamp_");
        strncpy(VDIF_timestamp_filename+15,&argv[2][34],4);
        strcpy(VDIF_timestamp_filename+19,"_");
        strncpy(VDIF_timestamp_filename+20,&argv[2][11],1);
        strcpy(VDIF_timestamp_filename+21,".text");

        
        strcpy(VDIF_timestamp_jump_filename,"VDIF_timestamp_jump_");
        strncpy(VDIF_timestamp_jump_filename+20,&argv[2][34],4);
        strcpy(VDIF_timestamp_jump_filename+24,"_");
        strncpy(VDIF_timestamp_jump_filename+25,&argv[2][11],1);
        strcpy(VDIF_timestamp_jump_filename+26,".text");

		printf("VDIF_timestamp_jump_ is %s,%s\n",VDIF_timestamp_filename,VDIF_timestamp_jump_filename);

		VDIF_timestamp_file=fopen(VDIF_timestamp_filename,"w");
        VDIF_timestamp_jump_file=fopen(VDIF_timestamp_jump_filename,"w");
        //Error_ROACH2_id=fopen("Error_ROACH2_id_file.text","w");
    
	if (argc < 3) {
		fprintf(stdout,"Usage: %s NUMPACKETS SGFILE [ SGFILE [ ... ] ]\n",&argv[0][2]);
		return 1;
	}
	num_packets = atoi(argv[1]);
	num_files = argc - 2;
	if (open_group_sg(num_files,&argv[2],&group) != -1) {
		packets_read = 0;
		while (packets_read<num_packets) {
			if (num_packets-packets_read<2000) {
				ii = read_packets_from_group_sg(&group,
				  num_packets-packets_read,&buf);
				packets_read += ii;
			} else {
				ii = read_packets_from_group_sg(&group,
				  2000,&buf);
				packets_read += ii;
			}
			if (ii==0) {
				break;
			}
			pkt1 = (vdif_header_t *)buf;
			pkt_size_8byte = pkt1->frame_length;
			VDIF_pkt_len=8*pkt_size_8byte;
			VTP_len=8;
			B_engine_pkt_num_per_VDIF=8;
			VTP_num_per_VDIF=B_engine_pkt_num_per_VDIF-1;
			B_engine_pkt_len=(VDIF_pkt_len-VTP_len*VTP_num_per_VDIF)/B_engine_pkt_num_per_VDIF;

			//printf("frame length:%d\n",pkt_size_8byte);
			pkt2 = (vdif_header_t *)(buf + 8*pkt_size_8byte*(ii-1));
			//fprintf(stdout,"VDIF time is %d@%d+%d .. %d@%d+%d\n",
			//  pkt1->ref_epoch,pkt1->secs_since_epoch,pkt1->data_frame,
			//  pkt2->ref_epoch,pkt2->secs_since_epoch,pkt2->data_frame);

            
            for(cnt_pkt=0;cnt_pkt<ii;cnt_pkt++)
			{

				for(cnt_B_engine=0; cnt_B_engine<B_engine_pkt_num_per_VDIF; cnt_B_engine=cnt_B_engine+1)
				{
                    B_engine_pkt_0 = (vdif_header_t *)(buf + 8*pkt_size_8byte*cnt_pkt + cnt_B_engine*(B_engine_pkt_len+VTP_len));
					b_engine_Fid_tmp = (uint32_t) B_engine_pkt_0->beng.f;

					if(b_engine_Fid_tmp==ROACH_id_0)
					{
						b_engine_tmp=0;
					    b_engine_tmp |= (int64_t)(B_engine_pkt_0->beng.b_upper) << 21;
					    b_engine_tmp |= (int64_t)(B_engine_pkt_0->beng.b_lower & 0x001FFFFF);
					    b_engine_clk_0 = (int32_t)( b_engine_tmp & (int64_t)0x000000001FFFFFFF);
					    b_engine_sec_0 = (int32_t)((b_engine_tmp & (int64_t)0x001FFFFFE0000000)>>29);
					    b_engine_Cid_0 = (uint32_t) B_engine_pkt_0->beng.c;
					    b_engine_Fid_0 = (uint32_t) B_engine_pkt_0->beng.f;

						diff_Cid_0=b_engine_Cid_0-previous_b_engine_Cid_0;
					    fprintf(timestamp_file_0, "%d@%d@%d@%d, %d\n", b_engine_sec_0, b_engine_clk_0, b_engine_Fid_0, b_engine_Cid_0, diff_Cid_0);
                        
						if(diff_Cid_0!=1 && diff_Cid_0!=-255)
				        {
							fprintf(timestamp_jump_file_0, "%d@%d@%d@%d, %d@%d@%d@%d, %d\n", previous_b_engine_sec_0, previous_b_engine_clk_0, previous_b_engine_Fid_0, previous_b_engine_Cid_0, b_engine_sec_0, b_engine_clk_0, b_engine_Fid_0, b_engine_Cid_0, diff_Cid_0);				    
					    }

						previous_b_engine_clk_0=b_engine_clk_0;
				        previous_b_engine_sec_0=b_engine_sec_0;
				        previous_b_engine_Cid_0=b_engine_Cid_0;
                        previous_b_engine_Fid_0=b_engine_Fid_0;

					}
					else if(b_engine_Fid_tmp==ROACH_id_1)
					{
						b_engine_tmp=0;
					    b_engine_tmp |= (int64_t)(B_engine_pkt_0->beng.b_upper) << 21;
					    b_engine_tmp |= (int64_t)(B_engine_pkt_0->beng.b_lower & 0x001FFFFF);
					    b_engine_clk_1 = (int32_t)( b_engine_tmp & (int64_t)0x000000001FFFFFFF);
					    b_engine_sec_1 = (int32_t)((b_engine_tmp & (int64_t)0x001FFFFFE0000000)>>29);
					    b_engine_Cid_1 = (uint32_t) B_engine_pkt_0->beng.c;
					    b_engine_Fid_1 = (uint32_t) B_engine_pkt_0->beng.f;

						diff_Cid_1=b_engine_Cid_1-previous_b_engine_Cid_1;
					    fprintf(timestamp_file_1, "%d@%d@%d@%d, %d\n", b_engine_sec_1, b_engine_clk_1, b_engine_Fid_1, b_engine_Cid_1, diff_Cid_1);

                        if(diff_Cid_1!=1 && diff_Cid_1!=-255)
				        {
						    fprintf(timestamp_jump_file_1, "%d@%d@%d@%d, %d@%d@%d@%d, %d\n", previous_b_engine_sec_1, previous_b_engine_clk_1, previous_b_engine_Fid_1, previous_b_engine_Cid_1, b_engine_sec_1, b_engine_clk_1, b_engine_Fid_1, b_engine_Cid_1, diff_Cid_1);				    
					    }

						previous_b_engine_clk_1=b_engine_clk_1;
				        previous_b_engine_sec_1=b_engine_sec_1;
				        previous_b_engine_Cid_1=b_engine_Cid_1;
                        previous_b_engine_Fid_1=b_engine_Fid_1;

					}
					else
					{

                                         //newly added
						b_engine_tmp=0;
					    b_engine_tmp |= (int64_t)(B_engine_pkt_0->beng.b_upper) << 21;
					    b_engine_tmp |= (int64_t)(B_engine_pkt_0->beng.b_lower & 0x001FFFFF);
					    b_engine_clk_error = (int32_t)( b_engine_tmp & (int64_t)0x000000001FFFFFFF);
					    b_engine_sec_error = (int32_t)((b_engine_tmp & (int64_t)0x001FFFFFE0000000)>>29);
					    b_engine_Cid_error = (uint32_t) B_engine_pkt_0->beng.c;
					    b_engine_Fid_error = (uint32_t) B_engine_pkt_0->beng.f;
						//printf("Another ROACH2 %d, Error\n",b_engine_Fid_tmp);
						fprintf(Error_ROACH2_id, "%d@%d@%d@%d\n", b_engine_sec_error, b_engine_clk_error, b_engine_Fid_error, b_engine_Cid_error);
						
					}

				}



                pkt3 = (vdif_header_t *)(buf + 8*pkt_size_8byte*cnt_pkt);
				VDIF_seconds=(uint32_t)pkt3->secs_since_epoch;
				VDIF_frame_index=(uint32_t)pkt3->data_frame;
				diff_VDIF_frame=VDIF_frame_index-previous_VDIF_frame_index;

				fprintf(VDIF_timestamp_file, "%d@%d, %d\n", VDIF_seconds, VDIF_frame_index, diff_VDIF_frame);

				if(diff_VDIF_frame!=1)
				{
					fprintf(VDIF_timestamp_jump_file, "%d@%d, %d@%d, %d\n", previous_VDIF_seconds, previous_VDIF_frame_index, VDIF_seconds, VDIF_frame_index, diff_VDIF_frame);
				}

				previous_VDIF_frame_index=VDIF_frame_index;
				previous_VDIF_seconds=VDIF_seconds;
	

			}
			
            

			free(buf);
		}
		close_group_sg(&group);
	}
	return 0;
}




