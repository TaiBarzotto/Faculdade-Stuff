const model = require("../models");

const obterTodosCursos = async () => {
	return await model.Curso.findAll();
};

// Função para obter curso por ID
const obterCursoPorId = async (curso) => {
	return await model.Curso.findByPk(curso.id);
};

// Função para criar um novo curso
const criarCurso = async (curso) => {
	await model.Curso.create(curso);
	return curso;
};

// Função para atualizar um curso
const atualizarCurso = async (curso) => {
	try {
		// Atualizar o curso
		await model.Curso.update(curso, { where: { id: curso.id } });

		// Retornar o curso atualizado
		return await model.Curso.findByPk(curso.id);
	} catch (error) {
		throw error;
	}
};

// Função para deletar um curso
const deletarCurso = async (curso) => {
	try {
		// Deletar o curso
		await model.Curso.destroy({ where: { id: curso.id } });

		return curso;
	} catch (error) {
		throw error;
	}
};

module.exports = {
	obterTodosCursos,
	obterCursoPorId,
	criarCurso,
	atualizarCurso,
	deletarCurso,
};
