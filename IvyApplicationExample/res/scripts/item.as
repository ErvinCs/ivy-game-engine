#include 'common.as'

class Item : IController
{
	ScriptableObject@ self;
	weakref<ScriptableObject> playerRef;
	bool collected = false;

	Item(ScriptableObject@ object)
	{
		@self = object;
	}

	void onUpdate()
	{
		ScriptableObject @player = playerRef;
		@player = FindObjectByTag('Player');
		@playerRef = player;
		

		if (not(collected) and not(player is null))
		{
			if (AreColliding(self.getOwner(), player.getOwner()))
			{
				collected = true;
				DestroySprite(self.getOwner());
				DestroyCollidable(self.getOwner());
				DestroyTransform(self.getOwner());
				self.sendMessage(CMessage('COLLECT'), player);
				self.kill();
			}		
		}

	}
}