const alunoRepository = require("../repositories/aluno-repository");

// Função para retornar todos os alunos
const retornaTodosAlunos = async (req, res) => {
	try {
		const alunos = await alunoRepository.obterTodosAlunos();
		res.status(200).json({ alunos: alunos });
	} catch (error) {
		console.log("Erro ao buscar alunos:", error);
		res.sendStatus(500);
	}
};

// Função para criar um novo aluno
const criaAluno = async (req, res) => {
	const { id, nome, email } = req.body;
	console.log({ id, nome, email });
	try {
		if (!id || !nome || !email) {
			return res
				.status(400)
				.json({ message: "ID, nome e email são obrigatórios." });
		}

		const aluno = await alunoRepository.criarAluno({
			id,
			nome,
			email,
		});
		res.status(201).json(aluno);
	} catch (error) {
		console.log("Erro ao criar aluno:", error);
		res.sendStatus(500);
	}
};

// Função para atualizar um aluno
const atualizaAluno = async (req, res) => {
	const { nome, email } = req.body;
	const id = parseInt(req.params.id);
	try {
		const alunoAtualizado = await alunoRepository.atualizarAluno({
			id,
			nome,
			email,
		});

		if (alunoAtualizado) {
			res.status(200).json(alunoAtualizado);
		} else {
			res.status(404).json({ message: "Aluno não encontrado" });
		}
	} catch (error) {
		console.log("Erro ao atualizar aluno:", error);
		res.sendStatus(500);
	}
};

// Função para deletar um aluno
const deletaAluno = async (req, res) => {
	try {
		const id = parseInt(req.params.id);
		const alunoRemovido = await alunoRepository.deletarAluno({ id });

		if (alunoRemovido) {
			res.status(200).json({
				message: "Aluno removido com sucesso.",
				aluno: alunoRemovido,
			});
		} else {
			res.status(404).json({ message: "Aluno não encontrado" });
		}
	} catch (error) {
		console.error("Erro ao deletar aluno:", error);
		res.status(500).json({ message: "Erro ao deletar aluno" });
	}
};

// Função para buscar aluno por ID
const retornaAlunoPorId = async (req, res) => {
	try {
		const id = parseInt(req.params.id);
		const aluno = await alunoRepository.obterAlunoPorId({
			id,
		});

		if (aluno) {
			res.status(200).json(aluno);
		} else {
			res.status(404).json({ message: "Aluno não encontrado." });
		}
	} catch (error) {
		console.log("Erro ao buscar aluno:", error);
		res.sendStatus(500);
	}
};

module.exports = {
	retornaTodosAlunos,
	criaAluno,
	atualizaAluno,
	deletaAluno,
	retornaAlunoPorId,
};
