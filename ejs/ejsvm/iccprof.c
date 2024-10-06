/*
 * eJS Project
 * Kochi University of Technology
 * The University of Electro-communications
 *
 * The eJS Project is the successor of the SSJS Project at The University of
 * Electro-communications.
 */

#include "prefix.h"
#define EXTERN extern
#include "header.h"

#ifdef USE_REGEXP
#define TYPE_SIZE 13
#else /* USE_REGEXP */
#define TYPE_SIZE 12
#endif /* USE_REGEXP */

typedef struct instruction_record{
  const char *name;
  int8_t operand_size;
  int64_t *table;
  struct instruction_record *next;
}InstructionRecord;

InstructionRecord *recordList = NULL;

void init_instruction_record(const char *name, InstructionRecord *record){
  record->name = name;
  record->operand_size = 0;
  record->table = NULL;
  record->next = NULL;
}

InstructionRecord *new_instruction_record(const char *name, InstructionRecord *prev){
  InstructionRecord *ret;
  ret = (InstructionRecord *)malloc(sizeof(InstructionRecord));
  if(ret == NULL)
    LOG_EXIT("Fail to allocate memory at new_instruction_record()");
  prev->next = ret;
  init_instruction_record(name, ret);
  return ret;
}

InstructionRecord *new_instruction_record_with_no_prev(const char *name){
  InstructionRecord *ret;
  ret = (InstructionRecord *)malloc(sizeof(InstructionRecord));
  if(ret == NULL)
    LOG_EXIT("Fail to allocate memory at new_instruction_record()");
  init_instruction_record(name, ret);
  return ret;
}

InstructionRecord *get_instruction_record_inner(const char *name, InstructionRecord *record){
  if(strcmp(record->name, name) == 0)
    return record;
  if(record->next == NULL){
    record->next = new_instruction_record(name, record);
    return record->next;
  }
  return get_instruction_record_inner(name, record->next);
}

InstructionRecord *get_instruction_record(const char *name){
  if(recordList == NULL){
    recordList = new_instruction_record_with_no_prev(name);
    return recordList;
  }
  return get_instruction_record_inner(name, recordList);
}

void icc_alloc_table(InstructionRecord *record, int operand_size){
  record->operand_size = operand_size;
  int size = TYPE_SIZE;
  int i;
  for(i=1; i<operand_size; i++)
    size *= TYPE_SIZE;
  record->table = (int64_t *)malloc(sizeof(int64_t)*size);
  if(record->table == NULL)
    LOG_EXIT("Fail to allocate memory at icc_inc_record1()");
  for(i=0; i<size; i++)
    record->table[i] = 0;
}

void icc_inc_record1(const char *name, JSValue v1){
  InstructionRecord *record = get_instruction_record(name);
  if(record->table == NULL)
    icc_alloc_table(record, 1);
  record->table[icc_value2index(v1)]++;
}

void icc_inc_record2(const char *name, JSValue v1, JSValue v2){
  InstructionRecord *record = get_instruction_record(name);
  if(record->table == NULL)
    icc_alloc_table(record, 2);
  record->table[icc_value2index(v1)+icc_value2index(v2)*TYPE_SIZE]++;
}

void icc_inc_record3(const char *name, JSValue v1, JSValue v2, JSValue v3){
  InstructionRecord *record = get_instruction_record(name);
  if(record->table == NULL)
    icc_alloc_table(record, 3);
  record->table[icc_value2index(v1)+icc_value2index(v2)*TYPE_SIZE+icc_value2index(v3)*TYPE_SIZE*TYPE_SIZE]++;
}

void print_instruction_record(FILE *fp, InstructionRecord *record){
  int i, j ,k;
  fprintf(fp, "#INSN %s %d\n", record->name, record->operand_size);
  switch(record->operand_size){
    case 1:
      for(i=0; i<TYPE_SIZE; i++){
        if(record->table[i] == 0) continue; /* Skips no called. */
        fprintf(fp, "#OPRN %s %ld\n", icc_index2type_name(i), record->table[i]);
      }
      break;
    case 2:
      for(j=0; j<TYPE_SIZE; j++){
        for(i=0; i<TYPE_SIZE; i++){
          if(record->table[i+TYPE_SIZE*j] == 0) continue; /* Skips no called. */
          fprintf(fp, "#OPRN %s,%s %ld\n", icc_index2type_name(i), icc_index2type_name(j), record->table[i+TYPE_SIZE*j]);
        }
      }
      break;
    case 3:
      for(k=0; k<TYPE_SIZE; k++){
        for(j=0; j<TYPE_SIZE; j++){
          for(i=0; i<TYPE_SIZE; i++){
            if(record->table[i+TYPE_SIZE*j+TYPE_SIZE*TYPE_SIZE*k] == 0) continue; /* Skips no called. */
            fprintf(fp, "#OPRN %s,%s,%s %ld\n", icc_index2type_name(i), icc_index2type_name(j), icc_index2type_name(k),
              record->table[i+TYPE_SIZE*j+TYPE_SIZE*TYPE_SIZE*k]);
          }
        }
      }
      break;
    default:
      LOG_EXIT("Instruction records are expected less than 4 operands.");
  }
}

void write_icc_profile_inner(FILE *fp, InstructionRecord *record){
  if(record == NULL) return;
  print_instruction_record(fp, record);
  write_icc_profile_inner(fp, record->next);
}

void write_icc_profile(FILE *fp){
  write_icc_profile_inner(fp, recordList);
}
