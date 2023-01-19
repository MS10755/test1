#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/************************* 0.基 类 **********************/
typedef void* (*function1_t)(void * ,void* );
typedef void (*function2_t)(void*);
typedef struct {
	function1_t add;
	function2_t print;
}base_obj_t;

/************************* 1.string 类 **********************/
typedef struct{
	base_obj_t base_obj;
	char buf[128];
	uint8_t len;
}string_t;

void* string_add(void*a, void*b) {
	string_t* a_ = (string_t*)a;
	string_t* b_ = (string_t*)b;
	strcat(a_->buf,b_->buf);
	a_->len += strlen(b_->buf);
	return a_;
}
void string_print(void* a) {
	string_t* a_ = (string_t*)a;
	printf("%s\n", a_->buf);
}

static string_t* new_string(const char * str) {
	string_t* p = (string_t*)malloc(sizeof(string_t));
	if (!p)return NULL;
	p->base_obj.add = string_add;
	p->base_obj.print = string_print;
	memset(p->buf,0, sizeof(p->buf));
	int len = strlen(str);
	memcpy(p->buf,str, len);//演示用不做越界检查了
	p->len = len;
	return p;
}

/************************* 1.int 类 **********************/

typedef struct {
	base_obj_t base_obj;
	int number;
}int_t;

void* int_add(void* a, void* b) {
	int_t* a_ = (int_t*)a;
	int_t* b_ = (int_t*)b;
	a_->number += b_->number;
	return a_;
}
void int_print(void* a) {
	int_t* a_ = (int_t*)a;
	printf("%d\n", a_->number);
}

static int_t* new_int(int n) {
	int_t* p = (int_t*)malloc(sizeof(int_t));
	if (!p)return NULL;
	p->base_obj.add = int_add;
	p->base_obj.print = int_print;
	p->number = n;
	return p;
}

void* template_add(void * a, void* b) {
	base_obj_t* base_obj = (base_obj_t*)a;//转 base_obj 相当于退化到基类
	base_obj->add(a,b);
	return a;
}

void template_print(void* a) {
	base_obj_t* base_obj = (base_obj_t*)a;
	base_obj->print(a);
}

int main() {
	string_t* string1 = new_string("hello");
	string_t* string2 = new_string(" world");
	template_add(string1, string2);
	template_print(string1);

	int_t* a = new_int(123);
	int_t* b = new_int(456);
	template_add(a, b);
	template_print(a);

}