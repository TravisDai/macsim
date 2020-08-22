#ifndef _TRACE_READ_A64_H
#define _TRACE_READ_A64_H

#include "trace_read_cpu.h"

class a64_decoder_c : public cpu_decoder_c
{
public:
  a64_decoder_c(macsim_c *simBase, ofstream *dprint_output) : cpu_decoder_c(simBase, dprint_output) {
    m_trace_size = sizeof(trace_info_a64_s) - sizeof(uint64_t);
  }

private:
  void init_pin_convert();
  inst_info_s *convert_pinuop_to_t_uop(void *pi, trace_uop_s **trace_uop, int core_id, int sim_thread_id);
  void convert_dyn_uop(inst_info_s *info, void *pi, trace_uop_s *trace_uop, Addr rep_offset, int core_id);
  inst_info_s *get_inst_info(thread_s *thread_trace_info, int core_id, int sim_thread_id);
  void dprint_inst(void *t_info, int core_id, int thread_id);
};

#ifndef USING_QSIM

//> Memory barrier operands
typedef enum arm64_barrier_op : int {
  ARM64_BARRIER_INVALID = 0,
  ARM64_BARRIER_OSHLD = 0x1,
  ARM64_BARRIER_OSHST = 0x2,
  ARM64_BARRIER_OSH = 0x3,
  ARM64_BARRIER_NSHLD = 0x5,
  ARM64_BARRIER_NSHST = 0x6,
  ARM64_BARRIER_NSH = 0x7,
  ARM64_BARRIER_ISHLD = 0x9,
  ARM64_BARRIER_ISHST = 0xa,
  ARM64_BARRIER_ISH = 0xb,
  ARM64_BARRIER_LD = 0xd,
  ARM64_BARRIER_ST = 0xe,
  ARM64_BARRIER_SY = 0xf
} arm64_barrier_op;

//> Prefetch operations (PRFM)
typedef enum arm64_prefetch_op : int {
  ARM64_PRFM_INVALID = 0,
  ARM64_PRFM_PLDL1KEEP = 0x00 + 1,
  ARM64_PRFM_PLDL1STRM = 0x01 + 1,
  ARM64_PRFM_PLDL2KEEP = 0x02 + 1,
  ARM64_PRFM_PLDL2STRM = 0x03 + 1,
  ARM64_PRFM_PLDL3KEEP = 0x04 + 1,
  ARM64_PRFM_PLDL3STRM = 0x05 + 1,
  ARM64_PRFM_PLIL1KEEP = 0x08 + 1,
  ARM64_PRFM_PLIL1STRM = 0x09 + 1,
  ARM64_PRFM_PLIL2KEEP = 0x0a + 1,
  ARM64_PRFM_PLIL2STRM = 0x0b + 1,
  ARM64_PRFM_PLIL3KEEP = 0x0c + 1,
  ARM64_PRFM_PLIL3STRM = 0x0d + 1,
  ARM64_PRFM_PSTL1KEEP = 0x10 + 1,
  ARM64_PRFM_PSTL1STRM = 0x11 + 1,
  ARM64_PRFM_PSTL2KEEP = 0x12 + 1,
  ARM64_PRFM_PSTL2STRM = 0x13 + 1,
  ARM64_PRFM_PSTL3KEEP = 0x14 + 1,
  ARM64_PRFM_PSTL3STRM = 0x15 + 1,
} arm64_prefetch_op;

// from capstone arm64.h
typedef enum ARM64_OPCODE_ENUM_ {
  ARM64_INS_INVALID = 0,

  ARM64_INS_ABS,
  ARM64_INS_ADC,
  ARM64_INS_ADDHN,
  ARM64_INS_ADDHN2,
  ARM64_INS_ADDP,
  ARM64_INS_ADD,
  ARM64_INS_ADDV,
  ARM64_INS_ADR,
  ARM64_INS_ADRP,
  ARM64_INS_AESD,
  ARM64_INS_AESE,
  ARM64_INS_AESIMC,
  ARM64_INS_AESMC,
  ARM64_INS_AND,
  ARM64_INS_ASR,
  ARM64_INS_B,
  ARM64_INS_BFM,
  ARM64_INS_BIC,
  ARM64_INS_BIF,
  ARM64_INS_BIT,
  ARM64_INS_BL,
  ARM64_INS_BLR,
  ARM64_INS_BR,
  ARM64_INS_BRK,
  ARM64_INS_BSL,
  ARM64_INS_CBNZ,
  ARM64_INS_CBZ,
  ARM64_INS_CCMN,
  ARM64_INS_CCMP,
  ARM64_INS_CLREX,
  ARM64_INS_CLS,
  ARM64_INS_CLZ,
  ARM64_INS_CMEQ,
  ARM64_INS_CMGE,
  ARM64_INS_CMGT,
  ARM64_INS_CMHI,
  ARM64_INS_CMHS,
  ARM64_INS_CMLE,
  ARM64_INS_CMLT,
  ARM64_INS_CMTST,
  ARM64_INS_CNT,
  ARM64_INS_MOV,
  ARM64_INS_CRC32B,
  ARM64_INS_CRC32CB,
  ARM64_INS_CRC32CH,
  ARM64_INS_CRC32CW,
  ARM64_INS_CRC32CX,
  ARM64_INS_CRC32H,
  ARM64_INS_CRC32W,
  ARM64_INS_CRC32X,
  ARM64_INS_CSEL,
  ARM64_INS_CSINC,
  ARM64_INS_CSINV,
  ARM64_INS_CSNEG,
  ARM64_INS_DCPS1,
  ARM64_INS_DCPS2,
  ARM64_INS_DCPS3,
  ARM64_INS_DMB,
  ARM64_INS_DRPS,
  ARM64_INS_DSB,
  ARM64_INS_DUP,
  ARM64_INS_EON,
  ARM64_INS_EOR,
  ARM64_INS_ERET,
  ARM64_INS_EXTR,
  ARM64_INS_EXT,
  ARM64_INS_FABD,
  ARM64_INS_FABS,
  ARM64_INS_FACGE,
  ARM64_INS_FACGT,
  ARM64_INS_FADD,
  ARM64_INS_FADDP,
  ARM64_INS_FCCMP,
  ARM64_INS_FCCMPE,
  ARM64_INS_FCMEQ,
  ARM64_INS_FCMGE,
  ARM64_INS_FCMGT,
  ARM64_INS_FCMLE,
  ARM64_INS_FCMLT,
  ARM64_INS_FCMP,
  ARM64_INS_FCMPE,
  ARM64_INS_FCSEL,
  ARM64_INS_FCVTAS,
  ARM64_INS_FCVTAU,
  ARM64_INS_FCVT,
  ARM64_INS_FCVTL,
  ARM64_INS_FCVTL2,
  ARM64_INS_FCVTMS,
  ARM64_INS_FCVTMU,
  ARM64_INS_FCVTNS,
  ARM64_INS_FCVTNU,
  ARM64_INS_FCVTN,
  ARM64_INS_FCVTN2,
  ARM64_INS_FCVTPS,
  ARM64_INS_FCVTPU,
  ARM64_INS_FCVTXN,
  ARM64_INS_FCVTXN2,
  ARM64_INS_FCVTZS,
  ARM64_INS_FCVTZU,
  ARM64_INS_FDIV,
  ARM64_INS_FMADD,
  ARM64_INS_FMAX,
  ARM64_INS_FMAXNM,
  ARM64_INS_FMAXNMP,
  ARM64_INS_FMAXNMV,
  ARM64_INS_FMAXP,
  ARM64_INS_FMAXV,
  ARM64_INS_FMIN,
  ARM64_INS_FMINNM,
  ARM64_INS_FMINNMP,
  ARM64_INS_FMINNMV,
  ARM64_INS_FMINP,
  ARM64_INS_FMINV,
  ARM64_INS_FMLA,
  ARM64_INS_FMLS,
  ARM64_INS_FMOV,
  ARM64_INS_FMSUB,
  ARM64_INS_FMUL,
  ARM64_INS_FMULX,
  ARM64_INS_FNEG,
  ARM64_INS_FNMADD,
  ARM64_INS_FNMSUB,
  ARM64_INS_FNMUL,
  ARM64_INS_FRECPE,
  ARM64_INS_FRECPS,
  ARM64_INS_FRECPX,
  ARM64_INS_FRINTA,
  ARM64_INS_FRINTI,
  ARM64_INS_FRINTM,
  ARM64_INS_FRINTN,
  ARM64_INS_FRINTP,
  ARM64_INS_FRINTX,
  ARM64_INS_FRINTZ,
  ARM64_INS_FRSQRTE,
  ARM64_INS_FRSQRTS,
  ARM64_INS_FSQRT,
  ARM64_INS_FSUB,
  ARM64_INS_HINT,
  ARM64_INS_HLT,
  ARM64_INS_HVC,
  ARM64_INS_INS,

  ARM64_INS_ISB,
  ARM64_INS_LD1,
  ARM64_INS_LD1R,
  ARM64_INS_LD2R,
  ARM64_INS_LD2,
  ARM64_INS_LD3R,
  ARM64_INS_LD3,
  ARM64_INS_LD4,
  ARM64_INS_LD4R,

  ARM64_INS_LDARB,
  ARM64_INS_LDARH,
  ARM64_INS_LDAR,
  ARM64_INS_LDAXP,
  ARM64_INS_LDAXRB,
  ARM64_INS_LDAXRH,
  ARM64_INS_LDAXR,
  ARM64_INS_LDNP,
  ARM64_INS_LDP,
  ARM64_INS_LDPSW,
  ARM64_INS_LDRB,
  ARM64_INS_LDR,
  ARM64_INS_LDRH,
  ARM64_INS_LDRSB,
  ARM64_INS_LDRSH,
  ARM64_INS_LDRSW,
  ARM64_INS_LDTRB,
  ARM64_INS_LDTRH,
  ARM64_INS_LDTRSB,

  ARM64_INS_LDTRSH,
  ARM64_INS_LDTRSW,
  ARM64_INS_LDTR,
  ARM64_INS_LDURB,
  ARM64_INS_LDUR,
  ARM64_INS_LDURH,
  ARM64_INS_LDURSB,
  ARM64_INS_LDURSH,
  ARM64_INS_LDURSW,
  ARM64_INS_LDXP,
  ARM64_INS_LDXRB,
  ARM64_INS_LDXRH,
  ARM64_INS_LDXR,
  ARM64_INS_LSL,
  ARM64_INS_LSR,
  ARM64_INS_MADD,
  ARM64_INS_MLA,
  ARM64_INS_MLS,
  ARM64_INS_MOVI,
  ARM64_INS_MOVK,
  ARM64_INS_MOVN,
  ARM64_INS_MOVZ,
  ARM64_INS_MRS,
  ARM64_INS_MSR,
  ARM64_INS_MSUB,
  ARM64_INS_MUL,
  ARM64_INS_MVNI,
  ARM64_INS_NEG,
  ARM64_INS_NOT,
  ARM64_INS_ORN,
  ARM64_INS_ORR,
  ARM64_INS_PMULL2,
  ARM64_INS_PMULL,
  ARM64_INS_PMUL,
  ARM64_INS_PRFM,
  ARM64_INS_PRFUM,
  ARM64_INS_RADDHN,
  ARM64_INS_RADDHN2,
  ARM64_INS_RBIT,
  ARM64_INS_RET,
  ARM64_INS_REV16,
  ARM64_INS_REV32,
  ARM64_INS_REV64,
  ARM64_INS_REV,
  ARM64_INS_ROR,
  ARM64_INS_RSHRN2,
  ARM64_INS_RSHRN,
  ARM64_INS_RSUBHN,
  ARM64_INS_RSUBHN2,
  ARM64_INS_SABAL2,
  ARM64_INS_SABAL,

  ARM64_INS_SABA,
  ARM64_INS_SABDL2,
  ARM64_INS_SABDL,
  ARM64_INS_SABD,
  ARM64_INS_SADALP,
  ARM64_INS_SADDLP,
  ARM64_INS_SADDLV,
  ARM64_INS_SADDL2,
  ARM64_INS_SADDL,
  ARM64_INS_SADDW2,
  ARM64_INS_SADDW,
  ARM64_INS_SBC,
  ARM64_INS_SBFM,
  ARM64_INS_SCVTF,
  ARM64_INS_SDIV,
  ARM64_INS_SHA1C,
  ARM64_INS_SHA1H,
  ARM64_INS_SHA1M,
  ARM64_INS_SHA1P,
  ARM64_INS_SHA1SU0,
  ARM64_INS_SHA1SU1,
  ARM64_INS_SHA256H2,
  ARM64_INS_SHA256H,
  ARM64_INS_SHA256SU0,
  ARM64_INS_SHA256SU1,
  ARM64_INS_SHADD,
  ARM64_INS_SHLL2,
  ARM64_INS_SHLL,
  ARM64_INS_SHL,
  ARM64_INS_SHRN2,
  ARM64_INS_SHRN,
  ARM64_INS_SHSUB,
  ARM64_INS_SLI,
  ARM64_INS_SMADDL,
  ARM64_INS_SMAXP,
  ARM64_INS_SMAXV,
  ARM64_INS_SMAX,
  ARM64_INS_SMC,
  ARM64_INS_SMINP,
  ARM64_INS_SMINV,
  ARM64_INS_SMIN,
  ARM64_INS_SMLAL2,
  ARM64_INS_SMLAL,
  ARM64_INS_SMLSL2,
  ARM64_INS_SMLSL,
  ARM64_INS_SMOV,
  ARM64_INS_SMSUBL,
  ARM64_INS_SMULH,
  ARM64_INS_SMULL2,
  ARM64_INS_SMULL,
  ARM64_INS_SQABS,
  ARM64_INS_SQADD,
  ARM64_INS_SQDMLAL,
  ARM64_INS_SQDMLAL2,
  ARM64_INS_SQDMLSL,
  ARM64_INS_SQDMLSL2,
  ARM64_INS_SQDMULH,
  ARM64_INS_SQDMULL,
  ARM64_INS_SQDMULL2,
  ARM64_INS_SQNEG,
  ARM64_INS_SQRDMULH,
  ARM64_INS_SQRSHL,
  ARM64_INS_SQRSHRN,
  ARM64_INS_SQRSHRN2,
  ARM64_INS_SQRSHRUN,
  ARM64_INS_SQRSHRUN2,
  ARM64_INS_SQSHLU,
  ARM64_INS_SQSHL,
  ARM64_INS_SQSHRN,
  ARM64_INS_SQSHRN2,
  ARM64_INS_SQSHRUN,
  ARM64_INS_SQSHRUN2,
  ARM64_INS_SQSUB,
  ARM64_INS_SQXTN2,
  ARM64_INS_SQXTN,
  ARM64_INS_SQXTUN2,
  ARM64_INS_SQXTUN,
  ARM64_INS_SRHADD,
  ARM64_INS_SRI,
  ARM64_INS_SRSHL,
  ARM64_INS_SRSHR,
  ARM64_INS_SRSRA,
  ARM64_INS_SSHLL2,
  ARM64_INS_SSHLL,
  ARM64_INS_SSHL,
  ARM64_INS_SSHR,
  ARM64_INS_SSRA,
  ARM64_INS_SSUBL2,
  ARM64_INS_SSUBL,
  ARM64_INS_SSUBW2,
  ARM64_INS_SSUBW,
  ARM64_INS_ST1,
  ARM64_INS_ST2,
  ARM64_INS_ST3,
  ARM64_INS_ST4,
  ARM64_INS_STLRB,
  ARM64_INS_STLRH,
  ARM64_INS_STLR,
  ARM64_INS_STLXP,
  ARM64_INS_STLXRB,
  ARM64_INS_STLXRH,
  ARM64_INS_STLXR,
  ARM64_INS_STNP,
  ARM64_INS_STP,
  ARM64_INS_STRB,
  ARM64_INS_STR,
  ARM64_INS_STRH,
  ARM64_INS_STTRB,
  ARM64_INS_STTRH,
  ARM64_INS_STTR,
  ARM64_INS_STURB,
  ARM64_INS_STUR,
  ARM64_INS_STURH,
  ARM64_INS_STXP,
  ARM64_INS_STXRB,
  ARM64_INS_STXRH,
  ARM64_INS_STXR,
  ARM64_INS_SUBHN,
  ARM64_INS_SUBHN2,
  ARM64_INS_SUB,
  ARM64_INS_SUQADD,
  ARM64_INS_SVC,
  ARM64_INS_SYSL,
  ARM64_INS_SYS,
  ARM64_INS_TBL,
  ARM64_INS_TBNZ,
  ARM64_INS_TBX,
  ARM64_INS_TBZ,
  ARM64_INS_TRN1,
  ARM64_INS_TRN2,
  ARM64_INS_UABAL2,
  ARM64_INS_UABAL,
  ARM64_INS_UABA,
  ARM64_INS_UABDL2,
  ARM64_INS_UABDL,
  ARM64_INS_UABD,
  ARM64_INS_UADALP,
  ARM64_INS_UADDLP,
  ARM64_INS_UADDLV,
  ARM64_INS_UADDL2,
  ARM64_INS_UADDL,
  ARM64_INS_UADDW2,
  ARM64_INS_UADDW,
  ARM64_INS_UBFM,
  ARM64_INS_UCVTF,
  ARM64_INS_UDIV,
  ARM64_INS_UHADD,
  ARM64_INS_UHSUB,
  ARM64_INS_UMADDL,
  ARM64_INS_UMAXP,
  ARM64_INS_UMAXV,
  ARM64_INS_UMAX,
  ARM64_INS_UMINP,
  ARM64_INS_UMINV,
  ARM64_INS_UMIN,
  ARM64_INS_UMLAL2,
  ARM64_INS_UMLAL,
  ARM64_INS_UMLSL2,
  ARM64_INS_UMLSL,
  ARM64_INS_UMOV,
  ARM64_INS_UMSUBL,
  ARM64_INS_UMULH,
  ARM64_INS_UMULL2,
  ARM64_INS_UMULL,
  ARM64_INS_UQADD,
  ARM64_INS_UQRSHL,
  ARM64_INS_UQRSHRN,
  ARM64_INS_UQRSHRN2,
  ARM64_INS_UQSHL,
  ARM64_INS_UQSHRN,
  ARM64_INS_UQSHRN2,
  ARM64_INS_UQSUB,
  ARM64_INS_UQXTN2,
  ARM64_INS_UQXTN,
  ARM64_INS_URECPE,
  ARM64_INS_URHADD,
  ARM64_INS_URSHL,
  ARM64_INS_URSHR,
  ARM64_INS_URSQRTE,
  ARM64_INS_URSRA,
  ARM64_INS_USHLL2,
  ARM64_INS_USHLL,
  ARM64_INS_USHL,
  ARM64_INS_USHR,
  ARM64_INS_USQADD,
  ARM64_INS_USRA,
  ARM64_INS_USUBL2,
  ARM64_INS_USUBL,
  ARM64_INS_USUBW2,
  ARM64_INS_USUBW,
  ARM64_INS_UZP1,
  ARM64_INS_UZP2,
  ARM64_INS_XTN2,
  ARM64_INS_XTN,
  ARM64_INS_ZIP1,
  ARM64_INS_ZIP2,

  // alias insn
  ARM64_INS_MNEG,
  ARM64_INS_UMNEGL,
  ARM64_INS_SMNEGL,
  ARM64_INS_NOP,
  ARM64_INS_YIELD,
  ARM64_INS_WFE,
  ARM64_INS_WFI,
  ARM64_INS_SEV,
  ARM64_INS_SEVL,
  ARM64_INS_NGC,
  ARM64_INS_SBFIZ,
  ARM64_INS_UBFIZ,
  ARM64_INS_SBFX,
  ARM64_INS_UBFX,
  ARM64_INS_BFI,
  ARM64_INS_BFXIL,
  ARM64_INS_CMN,
  ARM64_INS_MVN,
  ARM64_INS_TST,
  ARM64_INS_CSET,
  ARM64_INS_CINC,
  ARM64_INS_CSETM,
  ARM64_INS_CINV,
  ARM64_INS_CNEG,
  ARM64_INS_SXTB,
  ARM64_INS_SXTH,
  ARM64_INS_SXTW,
  ARM64_INS_CMP,
  ARM64_INS_UXTB,
  ARM64_INS_UXTH,
  ARM64_INS_UXTW,
  ARM64_INS_IC,
  ARM64_INS_DC,
  ARM64_INS_AT,
  ARM64_INS_TLBI,

  ARM64_INS_ENDING,  // <-- mark the end of the list of insn
} ARM64_OPCODE;

#endif /* USING_QSIM */

static const char *a64_opcode_names[ARM64_INS_ENDING] = {
  "ARM64_INS_INVALID",

  "ARM64_INS_ABS", "ARM64_INS_ADC", "ARM64_INS_ADDHN", "ARM64_INS_ADDHN2", "ARM64_INS_ADDP", "ARM64_INS_ADD",
  "ARM64_INS_ADDV", "ARM64_INS_ADR", "ARM64_INS_ADRP", "ARM64_INS_AESD", "ARM64_INS_AESE", "ARM64_INS_AESIMC",
  "ARM64_INS_AESMC", "ARM64_INS_AND", "ARM64_INS_ASR", "ARM64_INS_B", "ARM64_INS_BFM", "ARM64_INS_BIC", "ARM64_INS_BIF",
  "ARM64_INS_BIT", "ARM64_INS_BL", "ARM64_INS_BLR", "ARM64_INS_BR", "ARM64_INS_BRK", "ARM64_INS_BSL", "ARM64_INS_CBNZ",
  "ARM64_INS_CBZ", "ARM64_INS_CCMN", "ARM64_INS_CCMP", "ARM64_INS_CLREX", "ARM64_INS_CLS", "ARM64_INS_CLZ",
  "ARM64_INS_CMEQ", "ARM64_INS_CMGE", "ARM64_INS_CMGT", "ARM64_INS_CMHI", "ARM64_INS_CMHS", "ARM64_INS_CMLE",
  "ARM64_INS_CMLT", "ARM64_INS_CMTST", "ARM64_INS_CNT", "ARM64_INS_MOV", "ARM64_INS_CRC32B", "ARM64_INS_CRC32CB",
  "ARM64_INS_CRC32CH", "ARM64_INS_CRC32CW", "ARM64_INS_CRC32CX", "ARM64_INS_CRC32H", "ARM64_INS_CRC32W",
  "ARM64_INS_CRC32X", "ARM64_INS_CSEL", "ARM64_INS_CSINC", "ARM64_INS_CSINV", "ARM64_INS_CSNEG", "ARM64_INS_DCPS1",
  "ARM64_INS_DCPS2", "ARM64_INS_DCPS3", "ARM64_INS_DMB", "ARM64_INS_DRPS", "ARM64_INS_DSB", "ARM64_INS_DUP",
  "ARM64_INS_EON", "ARM64_INS_EOR", "ARM64_INS_ERET", "ARM64_INS_EXTR", "ARM64_INS_EXT", "ARM64_INS_FABD",
  "ARM64_INS_FABS", "ARM64_INS_FACGE", "ARM64_INS_FACGT", "ARM64_INS_FADD", "ARM64_INS_FADDP", "ARM64_INS_FCCMP",
  "ARM64_INS_FCCMPE", "ARM64_INS_FCMEQ", "ARM64_INS_FCMGE", "ARM64_INS_FCMGT", "ARM64_INS_FCMLE", "ARM64_INS_FCMLT",
  "ARM64_INS_FCMP", "ARM64_INS_FCMPE", "ARM64_INS_FCSEL", "ARM64_INS_FCVTAS", "ARM64_INS_FCVTAU", "ARM64_INS_FCVT",
  "ARM64_INS_FCVTL", "ARM64_INS_FCVTL2", "ARM64_INS_FCVTMS", "ARM64_INS_FCVTMU", "ARM64_INS_FCVTNS", "ARM64_INS_FCVTNU",
  "ARM64_INS_FCVTN", "ARM64_INS_FCVTN2", "ARM64_INS_FCVTPS", "ARM64_INS_FCVTPU", "ARM64_INS_FCVTXN",
  "ARM64_INS_FCVTXN2", "ARM64_INS_FCVTZS", "ARM64_INS_FCVTZU", "ARM64_INS_FDIV", "ARM64_INS_FMADD", "ARM64_INS_FMAX",
  "ARM64_INS_FMAXNM", "ARM64_INS_FMAXNMP", "ARM64_INS_FMAXNMV", "ARM64_INS_FMAXP", "ARM64_INS_FMAXV", "ARM64_INS_FMIN",
  "ARM64_INS_FMINNM", "ARM64_INS_FMINNMP", "ARM64_INS_FMINNMV", "ARM64_INS_FMINP", "ARM64_INS_FMINV", "ARM64_INS_FMLA",
  "ARM64_INS_FMLS", "ARM64_INS_FMOV", "ARM64_INS_FMSUB", "ARM64_INS_FMUL", "ARM64_INS_FMULX", "ARM64_INS_FNEG",
  "ARM64_INS_FNMADD", "ARM64_INS_FNMSUB", "ARM64_INS_FNMUL", "ARM64_INS_FRECPE", "ARM64_INS_FRECPS", "ARM64_INS_FRECPX",
  "ARM64_INS_FRINTA", "ARM64_INS_FRINTI", "ARM64_INS_FRINTM", "ARM64_INS_FRINTN", "ARM64_INS_FRINTP",
  "ARM64_INS_FRINTX", "ARM64_INS_FRINTZ", "ARM64_INS_FRSQRTE", "ARM64_INS_FRSQRTS", "ARM64_INS_FSQRT", "ARM64_INS_FSUB",
  "ARM64_INS_HINT", "ARM64_INS_HLT", "ARM64_INS_HVC", "ARM64_INS_INS",

  "ARM64_INS_ISB", "ARM64_INS_LD1", "ARM64_INS_LD1R", "ARM64_INS_LD2R", "ARM64_INS_LD2", "ARM64_INS_LD3R",
  "ARM64_INS_LD3", "ARM64_INS_LD4", "ARM64_INS_LD4R",

  "ARM64_INS_LDARB", "ARM64_INS_LDARH", "ARM64_INS_LDAR", "ARM64_INS_LDAXP", "ARM64_INS_LDAXRB", "ARM64_INS_LDAXRH",
  "ARM64_INS_LDAXR", "ARM64_INS_LDNP", "ARM64_INS_LDP", "ARM64_INS_LDPSW", "ARM64_INS_LDRB", "ARM64_INS_LDR",
  "ARM64_INS_LDRH", "ARM64_INS_LDRSB", "ARM64_INS_LDRSH", "ARM64_INS_LDRSW", "ARM64_INS_LDTRB", "ARM64_INS_LDTRH",
  "ARM64_INS_LDTRSB",

  "ARM64_INS_LDTRSH", "ARM64_INS_LDTRSW", "ARM64_INS_LDTR", "ARM64_INS_LDURB", "ARM64_INS_LDUR", "ARM64_INS_LDURH",
  "ARM64_INS_LDURSB", "ARM64_INS_LDURSH", "ARM64_INS_LDURSW", "ARM64_INS_LDXP", "ARM64_INS_LDXRB", "ARM64_INS_LDXRH",
  "ARM64_INS_LDXR", "ARM64_INS_LSL", "ARM64_INS_LSR", "ARM64_INS_MADD", "ARM64_INS_MLA", "ARM64_INS_MLS",
  "ARM64_INS_MOVI", "ARM64_INS_MOVK", "ARM64_INS_MOVN", "ARM64_INS_MOVZ", "ARM64_INS_MRS", "ARM64_INS_MSR",
  "ARM64_INS_MSUB", "ARM64_INS_MUL", "ARM64_INS_MVNI", "ARM64_INS_NEG", "ARM64_INS_NOT", "ARM64_INS_ORN",
  "ARM64_INS_ORR", "ARM64_INS_PMULL2", "ARM64_INS_PMULL", "ARM64_INS_PMUL", "ARM64_INS_PRFM", "ARM64_INS_PRFUM",
  "ARM64_INS_RADDHN", "ARM64_INS_RADDHN2", "ARM64_INS_RBIT", "ARM64_INS_RET", "ARM64_INS_REV16", "ARM64_INS_REV32",
  "ARM64_INS_REV64", "ARM64_INS_REV", "ARM64_INS_ROR", "ARM64_INS_RSHRN2", "ARM64_INS_RSHRN", "ARM64_INS_RSUBHN",
  "ARM64_INS_RSUBHN2", "ARM64_INS_SABAL2", "ARM64_INS_SABAL",

  "ARM64_INS_SABA", "ARM64_INS_SABDL2", "ARM64_INS_SABDL", "ARM64_INS_SABD", "ARM64_INS_SADALP", "ARM64_INS_SADDLP",
  "ARM64_INS_SADDLV", "ARM64_INS_SADDL2", "ARM64_INS_SADDL", "ARM64_INS_SADDW2", "ARM64_INS_SADDW", "ARM64_INS_SBC",
  "ARM64_INS_SBFM", "ARM64_INS_SCVTF", "ARM64_INS_SDIV", "ARM64_INS_SHA1C", "ARM64_INS_SHA1H", "ARM64_INS_SHA1M",
  "ARM64_INS_SHA1P", "ARM64_INS_SHA1SU0", "ARM64_INS_SHA1SU1", "ARM64_INS_SHA256H2", "ARM64_INS_SHA256H",
  "ARM64_INS_SHA256SU0", "ARM64_INS_SHA256SU1", "ARM64_INS_SHADD", "ARM64_INS_SHLL2", "ARM64_INS_SHLL", "ARM64_INS_SHL",
  "ARM64_INS_SHRN2", "ARM64_INS_SHRN", "ARM64_INS_SHSUB", "ARM64_INS_SLI", "ARM64_INS_SMADDL", "ARM64_INS_SMAXP",
  "ARM64_INS_SMAXV", "ARM64_INS_SMAX", "ARM64_INS_SMC", "ARM64_INS_SMINP", "ARM64_INS_SMINV", "ARM64_INS_SMIN",
  "ARM64_INS_SMLAL2", "ARM64_INS_SMLAL", "ARM64_INS_SMLSL2", "ARM64_INS_SMLSL", "ARM64_INS_SMOV", "ARM64_INS_SMSUBL",
  "ARM64_INS_SMULH", "ARM64_INS_SMULL2", "ARM64_INS_SMULL", "ARM64_INS_SQABS", "ARM64_INS_SQADD", "ARM64_INS_SQDMLAL",
  "ARM64_INS_SQDMLAL2", "ARM64_INS_SQDMLSL", "ARM64_INS_SQDMLSL2", "ARM64_INS_SQDMULH", "ARM64_INS_SQDMULL",
  "ARM64_INS_SQDMULL2", "ARM64_INS_SQNEG", "ARM64_INS_SQRDMULH", "ARM64_INS_SQRSHL", "ARM64_INS_SQRSHRN",
  "ARM64_INS_SQRSHRN2", "ARM64_INS_SQRSHRUN", "ARM64_INS_SQRSHRUN2", "ARM64_INS_SQSHLU", "ARM64_INS_SQSHL",
  "ARM64_INS_SQSHRN", "ARM64_INS_SQSHRN2", "ARM64_INS_SQSHRUN", "ARM64_INS_SQSHRUN2", "ARM64_INS_SQSUB",
  "ARM64_INS_SQXTN2", "ARM64_INS_SQXTN", "ARM64_INS_SQXTUN2", "ARM64_INS_SQXTUN", "ARM64_INS_SRHADD", "ARM64_INS_SRI",
  "ARM64_INS_SRSHL", "ARM64_INS_SRSHR", "ARM64_INS_SRSRA", "ARM64_INS_SSHLL2", "ARM64_INS_SSHLL", "ARM64_INS_SSHL",
  "ARM64_INS_SSHR", "ARM64_INS_SSRA", "ARM64_INS_SSUBL2", "ARM64_INS_SSUBL", "ARM64_INS_SSUBW2", "ARM64_INS_SSUBW",
  "ARM64_INS_ST1", "ARM64_INS_ST2", "ARM64_INS_ST3", "ARM64_INS_ST4", "ARM64_INS_STLRB", "ARM64_INS_STLRH",
  "ARM64_INS_STLR", "ARM64_INS_STLXP", "ARM64_INS_STLXRB", "ARM64_INS_STLXRH", "ARM64_INS_STLXR", "ARM64_INS_STNP",
  "ARM64_INS_STP", "ARM64_INS_STRB", "ARM64_INS_STR", "ARM64_INS_STRH", "ARM64_INS_STTRB", "ARM64_INS_STTRH",
  "ARM64_INS_STTR", "ARM64_INS_STURB", "ARM64_INS_STUR", "ARM64_INS_STURH", "ARM64_INS_STXP", "ARM64_INS_STXRB",
  "ARM64_INS_STXRH", "ARM64_INS_STXR", "ARM64_INS_SUBHN", "ARM64_INS_SUBHN2", "ARM64_INS_SUB", "ARM64_INS_SUQADD",
  "ARM64_INS_SVC", "ARM64_INS_SYSL", "ARM64_INS_SYS", "ARM64_INS_TBL", "ARM64_INS_TBNZ", "ARM64_INS_TBX",
  "ARM64_INS_TBZ", "ARM64_INS_TRN1", "ARM64_INS_TRN2", "ARM64_INS_UABAL2", "ARM64_INS_UABAL", "ARM64_INS_UABA",
  "ARM64_INS_UABDL2", "ARM64_INS_UABDL", "ARM64_INS_UABD", "ARM64_INS_UADALP", "ARM64_INS_UADDLP", "ARM64_INS_UADDLV",
  "ARM64_INS_UADDL2", "ARM64_INS_UADDL", "ARM64_INS_UADDW2", "ARM64_INS_UADDW", "ARM64_INS_UBFM", "ARM64_INS_UCVTF",
  "ARM64_INS_UDIV", "ARM64_INS_UHADD", "ARM64_INS_UHSUB", "ARM64_INS_UMADDL", "ARM64_INS_UMAXP", "ARM64_INS_UMAXV",
  "ARM64_INS_UMAX", "ARM64_INS_UMINP", "ARM64_INS_UMINV", "ARM64_INS_UMIN", "ARM64_INS_UMLAL2", "ARM64_INS_UMLAL",
  "ARM64_INS_UMLSL2", "ARM64_INS_UMLSL", "ARM64_INS_UMOV", "ARM64_INS_UMSUBL", "ARM64_INS_UMULH", "ARM64_INS_UMULL2",
  "ARM64_INS_UMULL", "ARM64_INS_UQADD", "ARM64_INS_UQRSHL", "ARM64_INS_UQRSHRN", "ARM64_INS_UQRSHRN2",
  "ARM64_INS_UQSHL", "ARM64_INS_UQSHRN", "ARM64_INS_UQSHRN2", "ARM64_INS_UQSUB", "ARM64_INS_UQXTN2", "ARM64_INS_UQXTN",
  "ARM64_INS_URECPE", "ARM64_INS_URHADD", "ARM64_INS_URSHL", "ARM64_INS_URSHR", "ARM64_INS_URSQRTE", "ARM64_INS_URSRA",
  "ARM64_INS_USHLL2", "ARM64_INS_USHLL", "ARM64_INS_USHL", "ARM64_INS_USHR", "ARM64_INS_USQADD", "ARM64_INS_USRA",
  "ARM64_INS_USUBL2", "ARM64_INS_USUBL", "ARM64_INS_USUBW2", "ARM64_INS_USUBW", "ARM64_INS_UZP1", "ARM64_INS_UZP2",
  "ARM64_INS_XTN2", "ARM64_INS_XTN", "ARM64_INS_ZIP1", "ARM64_INS_ZIP2",

  // alias insn
  "ARM64_INS_MNEG", "ARM64_INS_UMNEGL", "ARM64_INS_SMNEGL", "ARM64_INS_NOP", "ARM64_INS_YIELD", "ARM64_INS_WFE",
  "ARM64_INS_WFI", "ARM64_INS_SEV", "ARM64_INS_SEVL", "ARM64_INS_NGC", "ARM64_INS_SBFIZ", "ARM64_INS_UBFIZ",
  "ARM64_INS_SBFX", "ARM64_INS_UBFX", "ARM64_INS_BFI", "ARM64_INS_BFXIL", "ARM64_INS_CMN", "ARM64_INS_MVN",
  "ARM64_INS_TST", "ARM64_INS_CSET", "ARM64_INS_CINC", "ARM64_INS_CSETM", "ARM64_INS_CINV", "ARM64_INS_CNEG",
  "ARM64_INS_SXTB", "ARM64_INS_SXTH", "ARM64_INS_SXTW", "ARM64_INS_CMP", "ARM64_INS_UXTB", "ARM64_INS_UXTH",
  "ARM64_INS_UXTW", "ARM64_INS_IC", "ARM64_INS_DC", "ARM64_INS_AT", "ARM64_INS_TLBI"
  //"ARM64_INS_ENDING"  // <-- mark the end of the list of insn
};

#endif
