
//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i



/*complete the state machine*/

void Ping()
{
    switch(ping_state) //STATE TRANSITIONS
    {
        case PInit:
	    ping_state = PLow;
            break;
	case PHigh:
		ping_state = PLow;
		break;
	case PLow:
		ping_state = (i % 10 == 0) ? PHigh: PLow;
		break;
        default:
            ping_state = PInit;
            break;
    }
    switch(ping_state) //STATE ACTIONS
    {
        case PInit:
            break;
	case PHigh:
		Ping = 0x01;
		break;
	case PLow:
		Ping = 0x00;
		break;	
        default:
            break;
    }
}
