#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/* 
   gcc -no-pie -g in.c -o out
*/

typedef void (*event_handler)(const char *, int);

struct session_context {
    event_handler server_logging;
    char session_id[16];
    uint32_t flags;
};

void log_event(const char *msg, int rating) {
    if (rating == -1) {
        printf("[STATUS]: %s\n", msg);
    } else {
        printf("[%s]: %d\n", msg, rating);
    }
}

int calculate_rating(){
    /*Saves and calculates rating, proprietary technology
    based on https://shorturl.at/kLKso*/
    return 0;
}

void win() {
    char flag[128];
    FILE *fp = fopen("flag.txt", "r");
    if (fp) {
        fgets(flag, sizeof(flag), fp);
        printf("%s\n", flag);
        fclose(fp);
    }
    exit(0);
}

static inline int validate_size(uint32_t sz) {
    size_t aligned = (sz + 7) & ~7;
    return (int)aligned; 
}

void process_stream() {
    uint32_t header[3];
    
    if (fread(header, 1, 12, stdin) < 10) exit(1);
    /*file magic*/
    if (header[0] != 0x564d576e) return;

    uint16_t t_len = (uint16_t)(header[1] & 0xFFFF);
    uint32_t d_len = header[2];

    char *title = malloc(t_len + 1);
    if (title) {
        fread(title, 1, t_len, stdin);
        title[t_len] = '\0';
    }
    //arbitraty large size, so my storage doesnt fill up
    if (validate_size(d_len) > 2048) {
        puts("Stream limit exceeded.");
        exit(1);
    }

    size_t stream_size = (size_t)(d_len + 0x40); 
    char *stream_buf = malloc(stream_size);
    
    struct session_context *ctx = malloc(sizeof(struct session_context));
    if (!ctx || !stream_buf) exit(1);

    ctx->server_logging = log_event;
    memcpy(ctx->session_id, "SESSION_ACTIVE", 14);

    fread(stream_buf, 1, d_len, stdin);

    if (title) {
        printf("Entry: ");
        printf(title); 
        printf("\n");
    }
    int rating = calculate_rating();
    free(title);
    ctx->server_logging("Rating", rating);
}

int main() {
    setvbuf(stdout, NULL, _IONBF, 0);
    process_stream();
    return 0;
}
