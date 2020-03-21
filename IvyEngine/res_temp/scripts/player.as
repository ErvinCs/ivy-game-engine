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
		@transform = FindTransform(self.getOwner());
		if (IsKeyDown(RIGHT))
		{
			if (transform.position.x < leftBorder)
			{
				transform.position.x += playerMoveSpeed * deltatime;
			}
		}
		else if (IsKeyDown(LEFT))
		{
			if (transform.position.x > rightBorder)
			{
				transform.position.x -= playerMoveSpeed * deltatime;
			}
		}

		if (IsKeyDown(UP))
		{
			isJumping = true;
		}

		if (isJumping)
		{
			jumpTime -= deltatime;
			if (jumpTime > constJumpTime / 2)
			{
				transform.position.y += playerMoveSpeed * jumpSpeed * deltatime;	
			}
			else if (jumpTime < constJumpTime / 2 && jumpTime > 0)
			{
				transform.position.y -= playerMoveSpeed * jumpSpeed * deltatime;
			}
			else
			{
				isJumping = false;
				jumpCooldown = 1.0f;
				jumpTime = constJumpTime;
			}
		}
	}
}