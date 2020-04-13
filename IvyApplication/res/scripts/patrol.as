#include 'common.as'

class Patrol : IController
{
	ScriptableObject@ self;
	Transform@ transform;
	Collidable@ collidable;
	Collidable@ otherCollidable;
	weakref<ScriptableObject> playerRef;

	float moveSpeed = 5;
	float leftMargin = -4;
	float rightMargin = 4;
	float patrolPosition = 0;
	bool direction = true;

	Patrol(ScriptableObject@ object)
	{
		@self = object;
	}

	void onUpdate()
	{
		@transform = FindTransform(self.getOwner());
		ScriptableObject @player = playerRef;
		if(player is null)
		{
			@player = FindObjectByTag('Player');
			@playerRef = player;
		}
		@collidable = FindCollidable(self.getOwner());
		@otherCollidable = FindCollidable(player.getOwner());

		if(direction) {
			transform.position.x += moveSpeed * deltatime;
			patrolPosition += moveSpeed * deltatime;
		} else {
			transform.position.x -= moveSpeed * deltatime;
			patrolPosition -= moveSpeed * deltatime;
		}

		if(patrolPosition <= leftMargin) {
			direction = true;
		} else if(patrolPosition >= rightMargin) {
			direction = false;
		}

		
		if (AreColliding(collidable, otherCollidable))
		{
			self.sendMessage(CMessage('ATK'), player);
		}
	}
}