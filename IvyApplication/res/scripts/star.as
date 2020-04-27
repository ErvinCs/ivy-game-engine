#include 'common.as'

class Star : IController
{
	ScriptableObject@ self;
	Collidable@ collidable;
	Collidable@ playerCollidable;
	weakref<ScriptableObject> playerRef;

	Star(ScriptableObject@ object)
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

		if (AreColliding(collidable, playerCollidable))
		{
			self.sendMessage(CMessage('COLLECT'), player);
			self.kill();
		}
	}
}