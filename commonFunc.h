#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_CYAN    "\x1b[96m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define MARCINI 126
#define MAXPATH 1024
#define TIMEOUTMILLIS 500
#define MAXBUFF 67
#define MAXDATA 63

typedef enum
{ 
    BACKUP = 0, 
    BACKUPN,
    RECOVER,
    RECOVERN,
    CHOOSE_SER_DIR,
    VERIFY,
    FILENAME_RECOVER,
    MMD5,
    DATA,
    ENDOF,
    ENDGF,
    END,
    ERROR=12,
    OK,
    ACK,
    NACK
} type_t ;


typedef struct mensagem_t{
    unsigned char tamanho;
    unsigned char sequencia;
    unsigned char tipo;
    unsigned char dados[MAXDATA];

}mensagem_t;

int create_socket(char *interface_rede);

int fillBuffer(mensagem_t* msg, unsigned char* buffer);

int separateMessage(mensagem_t* msg, unsigned char* buffer);

DIR* openDir(char* path);

FILE* openFile(char* path,char* action);

void setMsgAttr(mensagem_t* m,unsigned char tamanho,unsigned char sequencia, unsigned char tipo);

void addToSeq(unsigned char* seq,int a);

unsigned char getSeqAdding(unsigned char* seq,int a);

int verifyMsg(unsigned char* buffer,int size);

void sendEmpty(int s,unsigned char seq,unsigned char tipo);

int recvMensagem(int s,unsigned char tipo,unsigned char* seq);

int getFileSize(FILE* f);

int fileExists(char* filename, char* dirname);

unsigned char* getMD5(FILE* fileClient);

int compareMD5(unsigned char* md5_1, unsigned char* md5_2);

int recvMD5Mensagem(int s, unsigned char* seq,char* path);
