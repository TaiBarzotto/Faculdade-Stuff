const cursoRepository = require("../repositories/curso-repository");

// Função para retornar todos os curso
const retornaTodosCursos = async (req, res) => {
	try {
		const curso = await cursoRepository.obterTodosCursos();
		res.status(200).json({ curso: curso });
	} catch (error) {
		console.log("Erro ao buscar curso:", error);
		res.sendStatus(500);
	}
};

// Função para criar um novo curso
const criaCurso = async (req, res) => {
	const { id, descricao } = req.body;
	try {
		if (!id || !descricao) {
			return res
				.status(400)
				.json({ message: "ID e descrição são obrigatórios." });
		}

		const curso = await cursoRepository.criarCurso({
			id,
			descricao,
		});
		res.status(201).json(curso);
	} catch (error) {
		console.log("Erro ao criar curso:", error);
		res.sendStatus(500);
	}
};

// Função para atualizar um curso
const atualizaCurso = async (req, res) => {
	const { descricao } = req.body;
	const id = parseInt(req.params.id);
	try {
		const cursoAtualizado = await cursoRepository.atualizarCurso({
			id,
			descricao,
		});

		if (cursoAtualizado) {
			res.status(200).json(cursoAtualizado);
		} else {
			res.status(404).json({ message: "curso não encontrado" });
		}
	} catch (error) {
		console.log("Erro ao atualizar curso:", error);
		res.sendStatus(500);
	}
};

// Função para deletar um curso
const deletaCurso = async (req, res) => {
	try {
		const id = parseInt(req.params.id);
		const cursoRemovido = await cursoRepository.deletarCurso({ id });

		if (cursoRemovido) {
			res.status(200).json({
				message: "curso removido com sucesso.",
				curso: cursoRemovido,
			});
		} else {
			res.status(404).json({ message: "curso não encontrado" });
		}
	} catch (error) {
		console.error("Erro ao deletar curso:", error);
		res.status(500).json({ message: "Erro ao deletar curso" });
	}
};

// Função para buscar curso por ID
const retornaCursoPorId = async (req, res) => {
	try {
		const id = parseInt(req.params.id);
		const curso = await cursoRepository.obterCursoPorId({
			id,
		});

		if (curso) {
			res.status(200).json(curso);
		} else {
			res.status(404).json({ message: "curso não encontrado." });
		}
	} catch (error) {
		console.log("Erro ao buscar curso:", error);
		res.sendStatus(500);
	}
};

module.exports = {
	retornaTodosCursos,
	criaCurso,
	atualizaCurso,
	deletaCurso,
	retornaCursoPorId,
};
