enum Actions
{
	UP = 87,
	DOWN = 83,
	LEFT = 65,
	RIGHT = 68  
}

class CPlayer : IController
{
	ScriptableObject@ self;
	Transform@ transform;

	bool isJumping = false;
	bool isFalling = false;
	float playerMoveSpeed = 5;
	float constJumpTime = 1.3;
	float jumpTime = 1.3;
	float jumpSpeed = 2.0;
	float jumpCooldown = 1.0;

	float leftBorder = 12.3;
	float rightBorder = -11.8;
	float topBorder = 6.4;
	float botBorder = -6.4;

	CPlayer(ScriptableObject@ object)
	{
		@self = object;
	}

	void onUpdate()
	{
		GetTransform(self.getOwner(), transform);

		if (IsKeyDown(RIGHT))
		{
			if (transform.positionX < leftBorder)
			{
				transform.positionX += playerMoveSpeed;
			}
		}
		else if (IsKeyDown(LEFT))
		{
			if (transform.positionX > rightBorder)
			{
				transform.positionX -= playerMoveSpeed;
			}
		}

		if (IsKeyDown(UP))
		{
			isJumping = true;
		}
	}
}