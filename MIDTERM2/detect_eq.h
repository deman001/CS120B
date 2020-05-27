//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i



/*complete the state machine*/

void Detect_EQ()
{
    switch(detect_eq_state) //STATE TRANSITIONS
    {
        case DEQInit:
            //init variable(s) here.
            detect_eq_state = eqwait;
            break;
	case eqwait:
		detect_eq_state = Ping ? eqsample: eqwait;
		break;
	case eqsample:
		detect_eq_state = eqwait;
		break;
        default:
            detect_eq_state = DEQInit;
            break;
    }
    switch(detect_eq_state)
    {
        case DEQInit:
            break;
	case eqsample:
		unsigned char amp = PINA >> 3;
		EQDetect = (amp > 0) ? 0x02 : 0x00;
		break;
        default:
            break;
    }
}
