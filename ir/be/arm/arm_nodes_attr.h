#ifndef _ARM_NODES_ATTR_H_
#define _ARM_NODES_ATTR_H_

#include "../bearch.h"
#include "../../common/firm_types.h"

/** A register requirement. */
typedef struct _arm_register_req_t {
	const arch_register_req_t req;
	int same_pos;        /**< in case of "should be same" we need to remember the pos to get the irn */
	int different_pos;   /**< in case of "should be different" we need to remember the pos to get the irn */
} arm_register_req_t;

/**
 * Possible ARM register shift types.
 */
typedef enum _arm_shift_modifier {
	ARM_SHF_NONE = 0,   /**< no shift */
	ARM_SHF_IMM  = 1,   /**< immediate operand with implicit ROR */
	ARM_SHF_ASR  = 2,   /**< arithmetic shift right */
	ARM_SHF_LSL  = 3,   /**< logical shift left */
	ARM_SHF_LSR  = 4,   /**< logical shift right */
	ARM_SHF_ROR  = 5,   /**< rotate right */
	ARM_SHF_RRX  = 6,   /**< rotate with sign extend */
} arm_shift_modifier;

/** True, if the modifier implies a shift argument */
#define ARM_HAS_SHIFT(mod)          ((mod) > ARM_SHF_IMM)

/** get the shift modifier from flags */
#define ARM_GET_SHF_MOD(attr)       ((attr)->instr_fl & 7)

/** set the shift modifier to flags */
#define ARM_SET_SHF_MOD(attr, mod)  ((attr)->instr_fl = (((attr)->instr_fl & ~7) | (mod)))


/**
 * Possible ARM condition codes.
 */
typedef enum _arm_condition {
	ARM_COND_EQ = 0,   /**< Equal, Z set. */
	ARM_COND_NE = 1,   /**< Not Equal, Z clear */
	ARM_COND_CS = 2,   /**< Carry set, unsigned >=, C set */
	ARM_COND_CC = 3,   /**< Carry clear, unsigned <, C clear */
	ARM_COND_MI = 4,   /**< Minus/Negativ, N set */
	ARM_COND_PL = 5,   /**< Plus/Positiv or Zero, N clear */
	ARM_COND_VS = 6,   /**< Overflow, V set */
	ARM_COND_VC = 7,   /**< No overflow, V clear */
	ARM_COND_HI = 8,   /**< unsigned >, C set and Z clear */
	ARM_COND_LS = 9,   /**< unsigned <=, C clear or Z set */
	ARM_COND_GE = 10,  /**< signed >=, N == V */
	ARM_COND_LT = 11,  /**< signed <, N != V */
	ARM_COND_GT = 12,  /**< signed >, Z clear and N == V */
	ARM_COND_LE = 13,  /**< signed <=, Z set or N != V */
	ARM_COND_AL = 14,  /**< Always (unconditional) */
	ARM_COND_NV = 15   /**< forbidden */
} arm_condition;

/** Get the condition code from flags */
#define ARM_GET_COND(attr)        (((attr)->instr_fl >> 3) & 15)

/** Set the condition code to flags */
#define ARM_SET_COND(attr, code)  ((attr)->instr_fl = (((attr)->instr_fl & ~(15 << 3)) | ((code) << 3)))

typedef struct _arm_attr_t {
	arch_irn_flags_t flags;             /**< indicating if spillable, rematerializeable ... etc. */
	int              n_res;             /**< number of results for this node */

	const arm_register_req_t **in_req;  /**< register requirements for arguments */
	const arm_register_req_t **out_req; /**< register requirements for results */

	const arch_register_t **slots;      /**< register slots for assigned registers */

	unsigned instr_fl;									/**< condition code, shift modifier */
	tarval *value;											/**< immediate */
	const char *symconst_label;
	int proj_num;
	int n_projs;
	long default_proj_num;
} arm_attr_t;

/**
 * Returns the shift modifier string.
 */
const char *arm_shf_mod_name(arm_shift_modifier mod);

#endif /* _ARM_NODES_ATTR_H_ */
