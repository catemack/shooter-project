#include "bullet.hpp"
#include "glm/gtx/string_cast.hpp"

std::array<std::array<glm::vec3, 4>, 6> bulletBounds{ {
	{ glm::vec3(0.1f, -0.1f, -0.1f), glm::vec3(-0.1f, -0.1f, -0.1f), glm::vec3(0.1f, 0.1f, -0.1f), glm::vec3(-0.1f, 0.1f, -0.1f) },
	{ glm::vec3(0.1f, -0.1f, 0.1f), glm::vec3(-0.1f, -0.1f, 0.1f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(-0.1f, 0.1f, 0.1f) },
	{ glm::vec3(-0.1f, 0.1f, -0.1f), glm::vec3(-0.1f, 0.1f, 0.1f), glm::vec3(-0.1f, -0.1f, -0.1f), glm::vec3(-0.1f, -0.1f, 0.1f) },
	{ glm::vec3(0.1f, 0.1f, -0.1f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.1f, -0.1f, -0.1f), glm::vec3(0.1f, -0.1f, 0.1f) },
	{ glm::vec3(0.1f, -0.1f, -0.1f), glm::vec3(-0.1f, -0.1f, -0.1f), glm::vec3(0.1f, -0.1f, 0.1f), glm::vec3(-0.1f, -0.1f, 0.1f) },
	{ glm::vec3(0.1f, 0.1f, -0.1f), glm::vec3(-0.1f, 0.1f, -0.1f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(-0.1f, 0.1f, 0.1f) }
} };

glm::vec4 bulletColor(0.8, 0.8, 0.8, 1.0);

Bullet::Bullet(glm::vec3 position, glm::vec3 velocity) :
	Collidable(position, bulletBounds),
	Renderable("lit_color", "lit_color"),
	v(velocity),
	toBeDestroyed(false)
{
	Renderable::pos = position;

	ColorVertex vertices[36] = {
		{ bulletBounds[0][0], glm::vec3(0.0f, 0.0f, -1.0f), bulletColor },
		{ bulletBounds[0][1], glm::vec3(0.0f, 0.0f, -1.0f), bulletColor },
		{ bulletBounds[0][2], glm::vec3(0.0f, 0.0f, -1.0f), bulletColor },
		{ bulletBounds[0][2], glm::vec3(0.0f, 0.0f, -1.0f), bulletColor },
		{ bulletBounds[0][3], glm::vec3(0.0f, 0.0f, -1.0f), bulletColor },
		{ bulletBounds[0][1], glm::vec3(0.0f, 0.0f, -1.0f), bulletColor },

		{ bulletBounds[1][0], glm::vec3(0.0f, 0.0f, 1.0f), bulletColor },
		{ bulletBounds[1][1], glm::vec3(0.0f, 0.0f, 1.0f), bulletColor },
		{ bulletBounds[1][2], glm::vec3(0.0f, 0.0f, 1.0f), bulletColor },
		{ bulletBounds[1][2], glm::vec3(0.0f, 0.0f, 1.0f), bulletColor },
		{ bulletBounds[1][3], glm::vec3(0.0f, 0.0f, 1.0f), bulletColor },
		{ bulletBounds[1][1], glm::vec3(0.0f, 0.0f, 1.0f), bulletColor },

		{ bulletBounds[2][0], glm::vec3(-1.0f, 0.0f, 0.0f), bulletColor },
		{ bulletBounds[2][1], glm::vec3(-1.0f, 0.0f, 0.0f), bulletColor },
		{ bulletBounds[2][2], glm::vec3(-1.0f, 0.0f, 0.0f), bulletColor },
		{ bulletBounds[2][2], glm::vec3(-1.0f, 0.0f, 0.0f), bulletColor },
		{ bulletBounds[2][3], glm::vec3(-1.0f, 0.0f, 0.0f), bulletColor },
		{ bulletBounds[2][1], glm::vec3(-1.0f, 0.0f, 0.0f), bulletColor },

		{ bulletBounds[3][0], glm::vec3(1.0f, 0.0f, 0.0f), bulletColor },
		{ bulletBounds[3][1], glm::vec3(1.0f, 0.0f, 0.0f), bulletColor },
		{ bulletBounds[3][2], glm::vec3(1.0f, 0.0f, 0.0f), bulletColor },
		{ bulletBounds[3][2], glm::vec3(1.0f, 0.0f, 0.0f), bulletColor },
		{ bulletBounds[3][3], glm::vec3(1.0f, 0.0f, 0.0f), bulletColor },
		{ bulletBounds[3][1], glm::vec3(1.0f, 0.0f, 0.0f), bulletColor },

		{ bulletBounds[4][0], glm::vec3(0.0f, -1.0f, 0.0f), bulletColor },
		{ bulletBounds[4][1], glm::vec3(0.0f, -1.0f, 0.0f), bulletColor },
		{ bulletBounds[4][2], glm::vec3(0.0f, -1.0f, 0.0f), bulletColor },
		{ bulletBounds[4][2], glm::vec3(0.0f, -1.0f, 0.0f), bulletColor },
		{ bulletBounds[4][3], glm::vec3(0.0f, -1.0f, 0.0f), bulletColor },
		{ bulletBounds[4][1], glm::vec3(0.0f, -1.0f, 0.0f), bulletColor },

		{ bulletBounds[5][0], glm::vec3(0.0f, 1.0f, 0.0f), bulletColor },
		{ bulletBounds[5][1], glm::vec3(0.0f, 1.0f, 0.0f), bulletColor },
		{ bulletBounds[5][2], glm::vec3(0.0f, 1.0f, 0.0f), bulletColor },
		{ bulletBounds[5][2], glm::vec3(0.0f, 1.0f, 0.0f), bulletColor },
		{ bulletBounds[5][3], glm::vec3(0.0f, 1.0f, 0.0f), bulletColor },
		{ bulletBounds[5][1], glm::vec3(0.0f, 1.0f, 0.0f), bulletColor },
	};

	/* Set up vertex array object, vertex buffer */
	glGenVertexArrays(1, &mesh.vao);
	glGenBuffers(1, &mesh.vbo);

	/* Bind Vertex Array Object */
	glBindVertexArray(mesh.vao);

	/* Bind and set vertex buffer */
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ColorVertex) * 36, vertices, GL_STATIC_DRAW);

	/* Input data from vertex buffer */
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), (void*)0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), (void*)(2 * sizeof(glm::vec3)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), (void*)sizeof(glm::vec3));
}

void Bullet::move(float deltaTime)
{
	Collidable::displace(v * deltaTime);
	Renderable::pos = Collidable::getPos();
}

void Bullet::resolveCollision(const Wall& wall)
{
	toBeDestroyed = true;
}

bool Bullet::shouldCleanUp()
{
	return toBeDestroyed || outOfBounds();
}

bool Bullet::outOfBounds()
{
	glm::vec3 pos = Collidable::getPos();
	return (pos.x > 250.0f || pos.x < -250.0f ||
		pos.y > 250.0f || pos.y < -250.0f ||
		pos.z > 250.0f || pos.z < -250.0f);
}

const glm::vec3 Bullet::getVelocity() const
{
	return v;
}

void Bullet::draw(const Camera& camera)
{
	draw(camera, glm::vec3(1.0, 1.0, 1.0), 1.0);
}

void Bullet::draw(const Camera& camera, const glm::vec3 lightColor, const float lightIntensity)
{
	/* Set transform matrix */
	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::translate(transform, Renderable::pos);

	/* Set projection matrix */
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)WindowWidth / (float)WindowHeight, 0.1f, 100.0f);

	/* Set view matrix */
	glm::mat4 view = camera.getViewMatrix();

	/* Set normal matrix */
	glm::mat3 normal = glm::mat3(glm::transpose(glm::inverse(transform)));

	/* Set shaders */
	shader.use();

	/* Set vertices and indices */
	glBindVertexArray(mesh.vao);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);

	shader.setMat4("view", view);
	shader.setMat4("transform", transform);
	shader.setMat4("projection", projection);
	shader.setMat3("normal_mat", normal);

	shader.setVec3("ambient_light_color", lightColor);
	shader.setFloat("ambient_light_strength", lightIntensity);

	shader.setVec3("view_pos", camera.getPos());

	/* Draw triangles */
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
