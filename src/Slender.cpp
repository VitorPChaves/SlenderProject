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

/*----------SLENDER APPEARENCE-------------*/
// Uses used the time elapsed to count every second that 
// Slender will appear or not.
void Slender::slenderMechanics(Shader& slenderShader) {
	auto time = timeElapsed();

	std::cout << time << std::endl;

	//the slender will appear each "multiplier(i) * 10"
	if (time >= time_aux) {
		showSlender = !showSlender;
		i += 1.0;
		time_aux += (i * 10);
		std::cout << "passs here" << std::endl;
		std::cout << "passs here" << std::endl;
		std::cout << "passs here" << std::endl;
	}

	if (showSlender) {
		slenderShader.use();

		glm::mat4 model = glm::mat4(1.0f);
		model = translate(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = scale(model, glm::vec3(0.2f, 0.2f, 0.2f));

		slenderShader.setMat4("model", model);

		slenderModel->Draw(slenderShader);
		glEnable(GL_FRAMEBUFFER_SRGB);
	}
}