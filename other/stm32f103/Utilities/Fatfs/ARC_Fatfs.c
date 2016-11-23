/**
  ******************************************************************************
  * @file    ARC_Fatfs.c
  * @author  armrunc (www.armrunc.com)
  * @version V1.0.0
  * @brief   ARC middleware. 
  *          This file provides ADC middleware functions.
  ******************************************************************************
  * @copy
  *
  * For non-commercial research and private study only.
  *
  * <h2><center>&copy; COPYRIGHT www.armrunc.com </center></h2>
  */ 

  
/* Includes ------------------------------------------------------------------*/
#include "ARC_Fatfs.h"
#include <stdio.h>
#include <stdlib.h>
#include "ff.h"
#include "integer.h"
#include "diskio.h"
#include <string.h>

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup ARC_FATFS
  * @{
  */ 

/** @defgroup ARC_FATFS_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_FATFS_Private_Defines
  * @{
  */

/**
  * @}
  */ 

/** @defgroup ARC_FATFS_Private_Macros
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup ARC_FATFS_Private_Variables
  * @{
  */ 

/**
  * @}
  */

/** @defgroup ARC_FATFS_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_FATFS_Private_Functions
  * @{
  */

void ARC_fat_menu_init(void)
{
    uint8_t key = 0;
    while (1)
    {
        printf("\nplease choose...\n");
        printf("format--------------------------------- f\n");
        printf("create file ----------------------------c\n");
        printf("delete file ----------------------------d\n");
        printf("list files -----------------------------l\n");
        printf("reboot   ------------------------------ s\n");
        printf("disk info ------------------------------i\n");
        printf("create folder --------------------------t\n");
        printf("edit file ------------------------------e\n");
        printf("read file ------------------------------r\n");
        key = getchar();
        printf("\n");
        switch (key)
        {
            case 'f':           //Format
                ARC_format_disk();
                break;
                  
            case 'c':           //Creat File
                ARC_creat_file();
                break;
                
            case 'd':           //Delete File
                ARC_delete_file();
                break;
                
            case 'l':           //list Files
                ARC_list_file();
                break;
                
            case 'i':           //Disk info
                ARC_get_disk_info();
                break;
                
            case 't':           //Creat Dir
                ARC_creat_dir();
                break;
                
            case 'e':           //Edit File
                ARC_edit_file();
                break;
                
            case 'r':           //Read File
                ARC_read_file();
                break;
                
            case 's':           //soft reset
                ARC_Sys_Soft_Reset();
                break;
                
            default:
                printf("invalid input, try again\n");
                break;
        }
    }
}

void ARC_edit_file(void)
{
    FATFS fs;
    FIL file;
    FRESULT res; 
    DIR dirs;
    FILINFO finfo;
    char key = 0;
    char path[20];

    uint32_t index = 0x00;
    uint32_t reindex = 0x00;
    uint8_t file_buff[512] = {0};

    uint32_t files_num = 0;
    res = f_mount(0,&fs);
    if (res != FR_OK)
    {
        printf("mont file system error, error code: %u\n",res);
        return;
    }
    res = f_opendir(&dirs,"/");
    printf("file list\n");
    if (res == FR_OK) 
    {
        while ((f_readdir(&dirs, &finfo) == FR_OK) && finfo.fname[0]) 
        {
            if (finfo.fattrib & AM_DIR) 
            { 
                continue;
            } 
            else 
            {   
                files_num++;
                printf("/%12s%7ld KB\n", &finfo.fname[0],(finfo.fsize + 512) / 1024);
            }
        }
        if( files_num == 0 )
        {
            printf("no file\n!");    
        }
    }
    else
    {
        printf("failed to open root directory, error code: %u\n", res);
    }
    printf("input the full name of the file, terminated with enter\n");
    scanf("%[^\n]",path);
    res = f_open(&file,path,FA_READ | FA_WRITE);
    if (res == FR_OK)
    {

        printf("file: %s opened successfully\n",path);
        printf("input the text!");
        printf("terminated with ESC or Ctrl+C\n");

        while(1)
        {
            key = getchar();
            if ((key == 0x1B) || (key == 0x03))   //key ESC or Ctrl + C
            {
                printf("saving data...\n");
                res = f_write(&file,file_buff,index,&reindex);
                if ((res == FR_OK) && (reindex == index))
                {
                    printf("data saved\n");
                    f_close(&file);
                    index = 0x00;
                    reindex = 0x00;
                }
                else
                {
                    printf("fail to save data, error code: %u", res);
                }
                break;
            }
            else
            {
                file_buff[index++] = key;
                if (index > 512)
                {
                    index = 0x00;
                }
            }
        }
    }
    else
    {
        printf("fail to open the file, error code: %u\n",res);
    }
}

void ARC_read_file(void)
{
    FATFS fs;
    FIL file;
    FRESULT res; 
    DIR dirs;
    FILINFO finfo;
    char path[20];
    char buffer[512] = {0};
    uint32_t i;
    uint32_t re,files_num = 0;
    res = f_mount(0,&fs);
    if (res != FR_OK)
    {
        printf("mont file system error, error code: %u\n",res);
        return;
    }
    res = f_opendir(&dirs,"/");
    if (res == FR_OK) 
    {
        printf("file list\n");
        while ((f_readdir(&dirs, &finfo) == FR_OK) && finfo.fname[0]) 
        {
            if (finfo.fattrib & AM_DIR)
            { 
                continue;
            } 
            else 
            {   
                files_num++;
                printf("/%12s%7ld KB\n",  &finfo.fname[0],(finfo.fsize + 512) / 1024);
            }
        }
        if( files_num == 0 )
        {
            printf("no files\n");
            return;
        }
    }
    else
    {
        printf("failed to open root directory, error code: %u\n", res);
    }
    printf("input the full name of the file, terminated with enter\n");
    scanf("%[^\n]",path);
    res = f_open(&file,path,FA_READ);
    printf("file opened\n");

    if (res == FR_OK)
    {
        while (1)
        {
            for(i = 0;i < 512;i++)
            {
                buffer[i] = 0x00;
            }
            res = f_read(&file,buffer,512,&re);
            printf("%s\n",buffer);

            if (res || re == 0)
            {
                printf("finish reading file, about to close the file!\n");
                f_close(&file);
                break;  
            }
        }
    }
    f_mount(0,NULL);
}

void ARC_creat_dir(void)
{
    FATFS fs;        
    FRESULT res;     
    char path[20];
    res = f_mount(0,&fs);
    if (res != FR_OK)
    {
        printf("mont file system error, error code: %u\n",res);
        return;
    }
    printf("please input the directory name terminated by enter\n");

    scanf("%[^\n]",path);

    res = f_mkdir(path);
    if (res == FR_OK)
    {
        printf("directory created successfully\n");
    }
    else
    {
        printf("failed to create directory, error code: %u", res);
    }
    f_mount(0,NULL);
}

void ARC_format_disk(void)
{
    FATFS fs;
    uint8_t res;
    res = f_mount(0,&fs);
    if (res != FR_OK)
    {
        printf("mont file system error, error code: %u\n",res);
        return;
    }
    printf("formating, may need up to minutes, please wait...\n");
    res = f_mkfs(0,1,4096);
    if (res == FR_OK)
    {
        printf("successful...\n");
    }
    else
    {
        printf("failed to format disk, error code: %u\n", res);
    }
    f_mount(0,NULL);
}

void ARC_creat_file(void)
{
    FIL file;
    FIL *pf = &file;
    FATFS fs;
    uint8_t res;
    uint8_t name[16] = {0};
    printf("please input file name, format: 8 + 3...\n");
    printf("for example:123.txt\n");
    scanf("%[^\n]",name);
    printf("name %s", name);
    res = f_mount(0, &fs);
    if (res != FR_OK)
    {
        printf("mont file system error, error code: %u\n",res);
        return;
    }
    res = f_open(pf,(const TCHAR *)name,FA_READ | FA_WRITE | FA_CREATE_NEW);
    if (res == FR_OK)
    {
        printf("file created successfully\n");
        res = f_close(pf);
        if (res != FR_OK)
        {
            printf("file created successfully, but failed to close\n");
            printf("error code: %u",res);
        }
    }
    else
    {
        printf("failed to create file, error code: %u", res);
    }
    f_mount(0,NULL);
}

void ARC_delete_file(void)
{
    FATFS fs;
    FRESULT res;
    uint8_t name[16] = {0};
    printf("please input the file name that you want to delete\n");
    scanf("%[^\n]",name);
    res = f_mount(0,&fs);
    if (res != FR_OK)
    {
        printf("mont file system error, error code: %u\n",res);
        return;
    }
    res = f_unlink((TCHAR *)name);

    if (res == FR_OK)
    {
        printf("file deleted successfully!\n");
    }
    else if (res == FR_NO_FILE)
    {
        printf("no such file or directory\n");
    }
    else if (res == FR_NO_PATH)
    {
        printf("no such path\n");
    }
    else
    {
        printf("error code: %u\n",res);
    }
    f_mount(0,NULL);
}

void ARC_list_file(void)
{
    FATFS fs;
    FILINFO finfo;
    FRESULT res;
    DIR dirs;
    int files_num = 0;
    res = f_mount(0, &fs);
    if (res != FR_OK)
    {
        printf("mont file system error, error code: %u\n",res);
        return;
    }
    res = f_opendir(&dirs, "/");
    if (res == FR_OK)
    {
        printf("------------ file list ------------\n");
        while ((f_readdir(&dirs, &finfo) == FR_OK) && finfo.fname[0]) 
        {
            if (finfo.fattrib & AM_DIR)//if Directory
            {
                files_num++;
                printf("/%s\n", &finfo.fname[0]);
            } 
            else 
            {
                continue;
            }
        }
    }
    else
    {
        printf("failed to open root directory, error code: %u\n", res);
    }
    res = f_opendir(&dirs, "/");
    if (res == FR_OK) 
    {
        while ((f_readdir(&dirs, &finfo) == FR_OK) && finfo.fname[0]) 
        {
            if (finfo.fattrib & AM_DIR) 
            { 
                continue;
            } 
            else 
            {   
                files_num++;
                printf("/.%12s%7ld KB \n",  &finfo.fname[0],(finfo.fsize + 512) / 1024);
            }
        }
        if( files_num == 0 )//no file
        {
            printf("no file!\n");    
        }
    }
    else
    {
        printf("failed to open root directory, error code: %u\n", res);
    }
    f_mount(0,NULL);
}

void ARC_get_disk_info(void)
{
    FATFS fs;
    FATFS *fls = &fs;
    FRESULT res;
    DWORD fre_clust,tot_sect,fre_sect;

    res = f_mount(0,&fs);
    if (res != FR_OK)
    {
        printf("mont file system error, error code: %u\n",res);
        return;
    }
    res = f_getfree("/",&fre_clust,&fls);
    if (res == FR_OK) 
    {
        tot_sect = (fls->n_fatent - 2) * fls->csize;
        fre_sect = fre_clust * fls->csize;

        
        /* Print free space in unit of KB (assuming 512 bytes/sector) */
        printf("%lu KB total drive space.\n"
               "%lu KB available.\n",
               fre_sect / 2, tot_sect / 2);
    }
    else
    {
        printf("failed to get disk info, error code: %u\n", res);
    }
    f_mount(0,NULL);
}

void ARC_Sys_Soft_Reset(void)
{   
    NVIC_SystemReset();
}

/**
  * @}
  */

/**
  * @}
  */
  
/**
  * @}
  */  
    
/******************* (C) www.armrunc.com *****END OF FILE****/
