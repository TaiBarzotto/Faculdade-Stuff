const matriculaRepository = require("../repositories/matricula-repository");

// Função para retornar todas as matriculas
const retornaTodasMatriculas = async (req, res) => {
	try {
		const matriculas = await matriculaRepository.obterTodasMatriculas();
		res.status(200).json({ matriculas: matriculas });
	} catch (error) {
		console.log("Erro ao buscar matriculas:", error);
		res.sendStatus(500);
	}
};

// Função para retornar todas as matriculas do aluno
const retornaMatriculaAluno = async (req, res) => {
	try {
		const matriculas = await matriculaRepository.obterMatriculaPorIdAluno(req.params.id_aluno);
		res.status(200).json({ matriculas: matriculas });
	} catch (error) {
		console.log("Erro ao buscar matriculas:", error);
		res.sendStatus(500);
	}
};

// Função para retornar todas as matriculas do curso
const retornaTodasMatriculasCurso = async (req, res) => {
	try {
		const matriculas = await matriculaRepository.obterMatriculaPorIdCurso(req.params.id_curso);
		res.status(200).json({ matriculas: matriculas });
	} catch (error) {
		console.log("Erro ao buscar matriculas:", error);
		res.sendStatus(500);
	}
};

// Função para criar um nova matricula
const criaMatricula = async (req, res) => {
	const { id_aluno, id_curso } = req.body;
	try {
		if (!id_aluno || !id_curso) {
			return res
				.status(400)
				.json({ message: "ID do aluno e curso são obrigatórios." });
		}

		const matricula = await matriculaRepository.criarMatricula({
			id_aluno,
			id_curso,
		});
		res.status(201).json(matricula);
	} catch (error) {
		console.log("Erro ao criar matricula:", error);
		res.sendStatus(500);
	}
};

// Função para atualizar uma matricula
const atualizaMatricula = async (req, res) => {
	const { id_curso } = req.body;
	const id_aluno = parseInt(req.params.id_aluno);

	try {
		const matriculaAtualizada =
			await matriculaRepository.atualizarMatricula({
				id_aluno,
				id_curso,
			});

		if (matriculaAtualizada) {
			res.status(200).json(matriculaAtualizada);
		} else {
			res.status(404).json({ message: "matricula não encontrada" });
		}
	} catch (error) {
		console.log("Erro ao atualizar matricula:", error);
		res.sendStatus(500);
	}
};

// Função para deletar uma matricula
const deletaMatricula = async (req, res) => {
	try {
		const id_aluno = parseInt(req.params.id_aluno);
		const matriculaRemovida = await matriculaRepository.deletarMatricula(id_aluno);

		if (matriculaRemovida) {
			res.status(200).json({
				message: "matricula removida com sucesso.",
				matricula: matriculaRemovida,
			});
		} else {
			res.status(404).json({ message: "matricula não encontrada" });
		}
	} catch (error) {
		console.error("Erro ao deletar matricula:", error);
		res.status(500).json({ message: "Erro ao deletar matricula" });
	}
};

module.exports = {
	retornaTodasMatriculas,
	retornaMatriculaAluno,
	retornaTodasMatriculasCurso,
	criaMatricula,
	atualizaMatricula,
	deletaMatricula,
};
