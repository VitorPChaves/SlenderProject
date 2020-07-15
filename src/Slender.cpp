#include <Slender.h>

/*********************************
NAO PODE OLHAR PRA ELE
ELE APARECE CONFORME DETERMINADO EVENTO
	*DEPENDENDO DO TIPO DE PISTA, ELE APARECE E NÃO DEIXA PEGAR
OBVIO QUE VAI TER CRONOMETRO PRA ELE APARECER
	*MAS ELE APARECE CONFORME PISTAS VÃO SENDO COLETADAS
**********************************/

Slender::Slender() {
	slenderModel = std::make_unique<Model>("../images/scene.gltf");
}

double Slender::timeElapsed() {
	return glfwGetTime();
}

float Slender::position() {
	srand(time(NULL));
	float pos = (rand() % 20) - 10;

	return pos;
}

/*----------SLENDER APPEARENCE-------------*/
// Uses used the time elapsed to count every second that 
// Slender will appear or not.
void Slender::slenderMechanics(Shader& slenderShader) {
	auto time = timeElapsed();

	float xPosition = position();
	float zPosition = position();
	
	std::cout << time << std::endl;

	//the slender will appear each "multiplier(i) * 10"
	if (time >= time_aux) {
		showSlender = !showSlender;
		i += 1.0;
		time_aux += (i * 10);

		/*std::cout << "passs here" << std::endl;
		std::cout << "passs here" << std::endl;
		std::cout << "passs here" << std::endl;*/
	}

	if (showSlender) {
		std::cout << "AAAA" << std::endl;

		slenderShader.use();

		glm::mat4 model = glm::mat4(1.0f);
		model = translate(model, glm::vec3(xPosition, 1.2, zPosition));
		model = scale(model, glm::vec3(0.9f, 0.9f, 0.9f));

		//slenderShader.setMat4("model", model);
		glEnable(GL_FRAMEBUFFER_SRGB);
		slenderModel->Draw(slenderShader);
	}
}