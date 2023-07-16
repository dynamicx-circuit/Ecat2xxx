

#ifndef C6T6_LM5116_KEY_H
#define C6T6_LM5116_KEY_H


unsigned char Enter_Key();

typedef struct {
    unsigned char key_select_num;
    unsigned char key_verify;
} press_key_t;

void press_key(press_key_t *press_key, unsigned char max_select_num);

#endif
