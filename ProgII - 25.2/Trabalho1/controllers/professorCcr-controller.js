const express = require("express");
const professorCcrService = require("../services/professorCcr-service");

const professorCcrRouter = express.Router();

// POST /professorCcr - Criar nova professorCcr
professorCcrRouter.post("/", professorCcrService.criaProfessorCcr);

// GET /professorCcrs - Retornar todas as professorCcrs
professorCcrRouter.get("/", professorCcrService.retornaTodosProfessorCcrs);

// GET /professorCcr/:id_professor - Retornar todas as professorCcrs do professor
professorCcrRouter.get("/professor/:id_professor", professorCcrService.retornaProfessorCcrProfessor);

// GET /professorCcr/:id_ccr - Retornar todas as professorCcrs do ccr
professorCcrRouter.get("/ccr/:id_ccr", professorCcrService.retornaTodosProfessorCcrsCcr);

// PUT /professorCcr/:id_professor - Atualizar professorCcr
professorCcrRouter.put("/:id_professor", professorCcrService.atualizaProfessorCcr);

// DELETE /professorCcr/:id_professor - Deletar professorCcr
professorCcrRouter.delete("/:id_professor", professorCcrService.deletaProfessorCcr);

module.exports = professorCcrRouter;