const express = require("express");
const ccrService = require("../services/ccr-service");

const ccrRouter = express.Router();

// POST /ccr - Criar novo ccr
ccrRouter.post("/", ccrService.criaCcr);

// GET /ccrs - Retornar todos os ccrs
ccrRouter.get("/todos", ccrService.retornaTodosCcrs);

// GET /ccr/:id - Retornar ccr por ID
ccrRouter.get("/:id", ccrService.retornaCcrPorId);

// GET /ccr/:id_curso - Retornar todas as ccrs do curso
ccrRouter.get("/curso/:id_curso", ccrService.retornaTodasCcrsCurso);

// PUT /ccr/:id - Atualizar ccr
ccrRouter.put("/:id", ccrService.atualizaCcr);

// DELETE /ccr/:id - Deletar ccr
ccrRouter.delete("/:id", ccrService.deletaCcr);

module.exports = ccrRouter;
