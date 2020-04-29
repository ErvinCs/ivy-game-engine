#include 'common.as'

class Item : IController
{
	ScriptableObject@ self;
	Collidable@ collidable;
	Collidable@ playerCollidable;
	weakref<ScriptableObject> playerRef;
	bool collected = false;

	Item(ScriptableObject@ object)
	{
		@self = object;
	}

	void onUpdate()
	{
		@collidable = FindCollidable(self.getOwner());
		ScriptableObject @player = playerRef;
		if(player is null)
		{
			@player = FindObjectByTag('Player');
			@playerRef = player;
		}
		if (not(player is null))
		{
			@playerCollidable = FindCollidable(player.getOwner());
		}

		if (not(collidable is null)) {
			if (not(collected) and AreColliding(collidable, playerCollidable))
			{
				DestroySprite(self.getOwner());
				DestroyCollidable(self.getOwner());
				DestroyTransform(self.getOwner());
				self.sendMessage(CMessage('COLLECT'), player);
				self.kill();
				
			}
		}
	}
}