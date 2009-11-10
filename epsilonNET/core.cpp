
#pragma managed
#using <mscorlib.dll>

#include "epsilon.h"

namespace Epsilon {

	public __sealed __gc struct Core {
		__property static int get_Version() {
			return EPS_VERSION;
		}
	
	private:
		Core() { }
	};

}
