#pragma once

namespace KEngine
{
	enum class eComponentType
	{
		Transform,
		SpriteRenderer,
		Animator,
		Script,
		Camera,

		End,
	};

	enum class eLayerType
	{
		None,
		BackGround,
		Animal,
		Player,
		Particle,

		Max = 16,
	};

	enum class eResourceType
	{
		Texture,
		AudioClip,
		Animation,
		Prefab,

		End,
	};
}
