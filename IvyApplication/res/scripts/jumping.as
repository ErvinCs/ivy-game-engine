class Jumping : IController
{
	ScriptableObject@ self;
	Transform@ transform;

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

	}
}