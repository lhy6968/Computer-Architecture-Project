#include<stdio.h>  
#include <iostream>
#include<malloc.h>

using namespace std;

void add_func (int* rs, int* rt,int* rd);
void addu_func (int* rs, int* rt,int* rd);
void addi_func (int* rs, int imm,int* rt);
void addiu_func (int* rs, int imm,int* rt);
void and_func (bool* rs, bool* rt,bool* rd);
void andi_func (bool* rs, bool* rt,int imm);
void div_func (int* rs,int* rt,int* lo,int* hi);
void divu_func (int* rs,int* rt,int* lo,int* hi);
void mult_func (int* rs,int* rt,int * lo,int* hi);
void multu_func (int* rs,int* rt,int * lo,int* hi);
void nor_func (bool* rs,bool* rt,bool* rd);
void or_func (bool* rs,bool* rt,bool* rd);
void ori_func(bool* rs,int imm,bool* rt);
void sll_func(int* rd,int* rt,int shamt);
void sllv_func(int* rd,int* rt,int* rs);
void sra_func(int* rd,int* rt,int shamt);
void srav_func(int* rd,int* rt,int* rs);
void srl_func(int* rd,int* rt,int shamt);
void srlv_func(int* rd,int* rt,int* rs);
void sub_func(int* rs,int* rt,int* rd);
void subu_func(int* rs,int* rt,int* rd);
void xor_func (bool* rs,bool* rt,bool* rd);
void xori_func (bool* rs,bool* rt,int imm);
void lui_func(int* rt,int imm);
void slt_func(int* rs,int* rt,int* rd);
void sltu_func(int* rs,int* rt,int* rd);
void beq_func(int*rs,int*rt,int pc,int offset);
void bgez_func(int* rs,int pc, int offset);
void bgezal_func(int* rs,int pc,int offset,int* ra);
void bgtz_func(int* rs,int pc,int offset);
void blez_func(int* rs,int pc,int offset);
void bltzal_func(int* rs,int pc,int offset,int* ra);
void bltz_func(int* rs,int pc,int offset);
void bne_func(int* rs,int *rt,int pc,int offset);

int main()  

{  
	void *rs = malloc(4);
	void *rt = malloc(4);
	void *rd = malloc(4);
	int* rs1=(int*)rs;
	*rs1 = 12;
	int* rt1=(int*)rt;
	*rt1 = 6;
	int* rd1=(int*)rd;
	*rd1 = 0;
	add_func(rs1,rt1,rd1);
	
	cout<<rd<<endl;
	cout<<rd1<<endl;
	bool a = true;
	int b = 1;
	bool c = a && b;
	if (c){
		cout<<"nihao"<<endl;
	}
	
	
    return 0;  

}

void add_func (int* rs, int* rt,int* rd){
	*rd = *rs + *rt;
}

void addu_func (int* rs, int* rt,int* rd){
	*rd = *rs + *rt;
}



void addiu_func (int* rs, int imm,int* rt){
	*rt = *rs + imm;
}

void and_func (bool* rs, bool* rt,bool* rd){
	*rd = *rs && rt;
}

void andi_func (bool* rs, bool* rt,int imm){
	*rt = *rs && imm;
}

void div_func (int* rs,int* rt,int* lo,int* hi){
	*lo = *rs / *rt;
	*hi = *rs % *rt;
}

void divu_func (int* rs,int* rt,int* lo,int* hi){
	*lo = *rs / *rt;
	*hi = *rs % *rt;
}

void mult_func (int* rs,int* rt,int * lo,int* hi){
	int result = (*rs) * (*rt);
	*hi = result / 65536;
	*lo = result % 65536;
	
}

void multu_func (int* rs,int* rt,int * lo,int* hi){
	int result = (*rs) * (*rt);
	*hi = result / 65536;
	*lo = result % 65536;	
}

void nor_func (bool* rs,bool* rt,bool* rd){
	*rd = not (*rs||*rt);
}

void or_func (bool* rs,bool* rt,bool* rd){
	*rd = *rs||*rt;
}

void ori_func(bool* rs,int imm,bool* rt){
	*rt = *rs||imm;
}

void sll_func(int* rd,int* rt,int shamt){
	*rd = (*rt) * pow(2,shamt);
}

void sllv_func(int* rd,int* rt,int* rs){
	*rd = (*rt) * pow(2,*rs);
}

void sra_func(int* rd,int* rt,int shamt){
	*rd = (*rt) / pow(2,shamt);
}

void srav_func(int* rd,int* rt,int* rs){
	*rd = (*rt) / pow(2,*rs);
}

void srl_func(int* rd,int* rt,int shamt){
	*rd = (*rt) / pow(2,shamt);
}

void srlv_func(int* rd,int* rt,int* rs){
	*rd = (*rt) / pow(2,*rs);
}

void sub_func(int* rs,int* rt,int* rd){
	*rd = abs(*rs-*rt);
}

void subu_func(int* rs,int* rt,int* rd){
	*rd = abs(*rs-*rt);
}

void xor_func (bool* rs,bool* rt,bool* rd){
	*rd = ((not *rs) && *rt )||((not *rt) && *rs);
}

void xori_func (bool* rs,bool* rt,int imm){
	*rt = ((not *rs) && imm )||((not imm) && *rs);
}

void lui_func(int* rt,int imm){
	int lowWord = imm % 65535;
	*rt = lowWord * 65536;
}

void slt_func(int* rs,int* rt,int* rd){
	if (*rs < *rt){
		*rd = 1;
	}
	else{
		*rd = 0;
	}
}

void sltu_func(int* rs,int* rt,int* rd){
	if (*rs < *rt){
		*rd = 1;
	}
	else{
		*rd = 0;
	}
}

void beq_func(int*rs,int*rt,int pc,int offset){
	if (*rs = *rt){
		pc = pc + offset*4;
	}
}

void bgez_func(int* rs,int pc, int offset){
	if (*rs >= 0){
		pc = pc + offset*4;
	}
}

void bgezal_func(int* rs,int pc,int offset,int* ra){
	if (*rs >= 0){
		pc = pc + offset*4;
		*ra = pc;
	}
}

void bgtz_func(int* rs,int pc,int offset){
	if (*rs > 0){
		pc = pc + offset*4;
	}
}

void blez_func(int* rs,int pc,int offset){
	if (*rs <= 0){
		pc = pc + offset*4;
	}
}

void bltzal_func(int* rs,int pc,int offset,int* ra){
	if (*rs < 0){
		pc = pc + offset*4;
		*ra = pc;
	}
}

void bltz_func(int* rs,int pc,int offset){
	if (*rs < 0){
		pc = pc + offset*4;
	}
}

void bne_func(int* rs,int *rt,int pc,int offset){
	if (*rs != *rt){
		pc = pc + offset*4;
	}
}

void j_func(int pc,int target){
	pc = 4194304 + (target - 1) * 4;
}

void jal_func(int pc, int* ra,int target){
	pc = 4194304 + (target - 1) * 4;
	*ra = pc;
}

void jalr_func(int* rs,int* rd,int pc){
	pc = *rs;
	*rd = pc;
}

void jr_func(int* rs,int pc){
	pc = *rs;
}

void teq_func(int* rs,int* rt){
	if (*rs == *rt){
		abort();
	}
}

void teqi_func(int* rs,int imm){
	if (*rs == imm){
		abort();
	}
}

void tne_func(int* rs,int* rt){
	if (*rs != *rt){
		abort();
	}
}

void tnei_func(int* rs,int imm){
	if (*rs != imm){
		abort();
	}
}

void tge_func(int* rs,int* rt){
	if (*rs >= *rt){
		abort();
	}
}

void tgeu_func(int* rs,int* rt){
	if (*rs >= *rt){
		abort();
	}
}

void tgei_func(int* rs,int imm){
	if (*rs >= imm){
		abort();
	}
}

void tgeiu_func(int* rs,int imm){
	if (*rs >= imm){
		abort();
	}
}

void tlt_func(int* rs,int* rt){
	if (*rs < *rt){
		abort();
	}
}

void tltu_func(int* rs,int* rt){
	if (*rs < *rt){
		abort();
	}
}

void tlti_func(*int rs,int imm){
	if (*rs < imm){
		abort();
	}
}

void tltiu_func(*int rs,int imm){
	if (*rs < imm){
		abort();
	}
}


void lb_func(int* rs,int* rt,int offset){
	int address = *rs + 4*offset;
	//这个地方调用假地址转真地址的函数，找到对应的数据
	*rt = 0; 
}

void lbu_func(int* rs,int* rt,int offset){
	int address = *rs + 4*offset;
	//这个地方调用假地址转真地址的函数，找到对应的数据
	*rt = 0; 
}

void lh_func(int* rs,int* rt,int offset){
	int address = *rs + 4*offset;
	//这个地方调用假地址转真地址的函数，找到对应的数据
	//取前16bit(%2^15)
	*rt = 0; 
}

void lhu_func(int* rs,int* rt,int offset){
	int address = *rs + 4*offset;
	//这个地方调用假地址转真地址的函数，找到对应的数据
	//取前16bit(%2^15)
	*rt = 0; 
}

void lw_func(int* rs,int* rt,int offset){
	int address = *rs + 4*offset;
	//这个地方调用假地址转真地址的函数，找到对应的数据
	*rt = 0; 
}

void lwl_func(int* rs,int* rt,int offset){
	int address = *rs + 4*offset;
	//这个地方调用假地址转真地址的函数，找到对应的数据
	//取前16bit(%2^15)
	*rt = 0; 
}

void lwr_func(int* rs,int* rt,int offset){
	int address = *rs + 4*offset;
	//这个地方调用假地址转真地址的函数，找到对应的数据
	//取后16bit(/2^15)
	*rt = 0; 
}

void ll_func(int* rs,int* rt,int offset){
	int address = *rs + 4*offset;
	//这个地方调用假地址转真地址的函数，找到对应的数据
	//还有个很长的功能 
	*rt = 0; 
}

void sb_func(int* rt,int offset){
	int number = *rt % 256;
	//根据偏移找到真地址并把number存入 
}

void sh_func(int* rt,int offset){
	int number = *rt % 65536;
	//根据偏移找到真地址并把number存入 
}

void sw_func(int* rt,int offset){
	//根据偏移找到真地址并把*rt存入 
} 

void swl_func(int* rt,int offset){
	int number = *rt % 256;
	//根据偏移找到真地址并把number存入 
}

void swr_func(int* rt,int offset){
	int number = *rt / 16777216;
	//根据偏移找到真地址并把number存入 
}

void sw_func(int* rt,int offset){
	//根据偏移找到真地址并把*rt存入 
} 

void mfhi_func(int* rd,int* hi){
	*rd = *hi;
}

void mflo_func(int* rd,int* lo){
	*rd = *lo;
}

viod mthi_func(int* rs,int* hi){
	*hi = *rs;
}

viod mtlo_func(int* rs,int* lo){
	*lo = *rs;
}

