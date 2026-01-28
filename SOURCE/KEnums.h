#pragma once

namespace KEngine
{
	enum class eLayerType
	{
		None,
		BackGround,
		Player,

		Max = 16,
	};

	enum class eResourceType
	{
		Texture,
		AudioClip,
		Prefab,


		End,
	};
}
