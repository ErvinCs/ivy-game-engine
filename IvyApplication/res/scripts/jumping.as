#include 'common.as'

class Jumping : IController
{
	ScriptableObject@ self;
	Transform@ transform;
	Collidable@ collidable;
	Collidable@ otherCollidable;
	weakref<ScriptableObject> playerRef;

	float moveSpeed = 5;
	float topMargin = -4;
	float botMargin = 4;
	float patrolPosition = 0;
	bool direction = true;

	Jumping(ScriptableObject@ object)
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
			transform.position.y += moveSpeed * deltatime;
			patrolPosition += moveSpeed * deltatime;
		} else {
			transform.position.y -= moveSpeed * deltatime;
			patrolPosition -= moveSpeed * deltatime;
		}

		if(patrolPosition <= topMargin) {
			direction = true;
		} else if(patrolPosition >= botMargin) {
			direction = false;
		}

		if (AreColliding(collidable, otherCollidable))
		{
			self.sendMessage(CMessage('ATK'), player);
		}

	}
}