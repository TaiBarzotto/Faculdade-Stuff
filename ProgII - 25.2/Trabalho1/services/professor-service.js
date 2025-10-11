const professorRepository = require("../repositories/professor-repository");

// Função para retornar todos os professores
const retornaTodosProfessores = async (req, res) => {
    try {
        const professores = await professorRepository.obterTodosProfessores();
        res.status(200).json({ professores: professores });
    } catch (error) {
        console.log("Erro ao buscar professores:", error);
        res.sendStatus(500);
    }
};

// Função para criar um novo professor
const criaProfessor = async (req, res) => {
    const { id, nome, email } = req.body;
    console.log({ id, nome, email });
    try {
        if (!id || !nome || !email) {
            return res
                .status(400)
                .json({ message: "ID, nome e email são obrigatórios." });
        }

        const professor = await professorRepository.criarProfessor({
            id,
            nome,
            email,
        });
        res.status(201).json(professor);
    } catch (error) {
        console.log("Erro ao criar professor:", error);
        res.sendStatus(500);
    }
};

// Função para atualizar um professor
const atualizaProfessor = async (req, res) => {
    const { nome, email } = req.body;
    const id = parseInt(req.params.id);
    try {
        const professorAtualizado = await professorRepository.atualizarProfessor({
            id,
            nome,
            email,
        });

        if (professorAtualizado) {
            res.status(200).json(professorAtualizado);
        } else {
            res.status(404).json({ message: "professor não encontrado" });
        }
    } catch (error) {
        console.log("Erro ao atualizar professor:", error);
        res.sendStatus(500);
    }
};

// Função para deletar um professor
const deletaProfessor = async (req, res) => {
    try {
        const id = parseInt(req.params.id);
        const professorRemovido = await professorRepository.deletarProfessor({ id });

        if (professorRemovido) {
            res.status(200).json({
                message: "professor removido com sucesso.",
                professor: professorRemovido,
            });
        } else {
            res.status(404).json({ message: "professor não encontrado" });
        }
    } catch (error) {
        console.error("Erro ao deletar professor:", error);
        res.status(500).json({ message: "Erro ao deletar professor" });
    }
};

// Função para buscar professor por ID
const retornaProfessorPorId = async (req, res) => {
    try {
        const id = parseInt(req.params.id);
        const professor = await professorRepository.obterProfessorPorId({
            id,
        });

        if (professor) {
            res.status(200).json(professor);
        } else {
            res.status(404).json({ message: "professor não encontrado." });
        }
    } catch (error) {
        console.log("Erro ao buscar professor:", error);
        res.sendStatus(500);
    }
};

module.exports = {
    retornaTodosProfessores,
    criaProfessor,
    atualizaProfessor,
    deletaProfessor,
    retornaProfessorPorId,
};
