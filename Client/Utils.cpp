#include "Framework.h"

App* app_;

void SetApp(App* app)
{
	app = app_;
}
App* GetApp() { return app_; }

