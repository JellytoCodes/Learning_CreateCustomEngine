#include "KResources.h"

namespace KEngine
{
	std::map<std::wstring, std::unique_ptr<Resource>> Resources::mResources = {};
}
