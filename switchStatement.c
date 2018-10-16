switch(opC)
{
	case 0000:
		HLT(operand);
		break;
	case 0001:
		LDR(operand);
		break;
	case 0010:
		STO(operand);
		break;
	case 0011:
		SUB(operand);
		break;
	case 0101:
		ADD(operand);
		break;
	case 0101:
		INP(operand);
		break;
	case 0110:
		OUT(operand);
		break;
	case 0111:
		SKP(operand);
		break;
	case 1000:
		JMP(operand);
		break;
	case 1001:
		AND(operand);
		break;
	case 1010:
		OR(operand);
		break;
	case 1011:
		MUL(operand);
		break;
}