#ifndef H_MAKER_CONTROLLER
#define H_MAKER_CONTROLLER

#include "controller.h"

class maker_controller : public controller
{
public:
	void setup_handlers() override;
	maker_controller();
};

#endif //H_MAKER_CONTROLLER