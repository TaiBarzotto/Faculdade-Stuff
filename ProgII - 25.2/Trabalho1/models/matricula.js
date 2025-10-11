"use strict";

module.exports = (sequelize, DataTypes) => {
	const Matricula = sequelize.define(
		"Matricula",
		{
			id_aluno: {
				type: DataTypes.INTEGER,
				primaryKey: true,
			},
			id_curso: {
				type: DataTypes.INTEGER,
				primaryKey: true,
			},
		},
		{
			sequelize,
			tableName: "matricula",
			schema: "public",
			freezeTableName: true,
			timestamps: false,
		},
	);

	Matricula.associate = function (models) {
		Matricula.belongsTo(models.Aluno, {
			foreignKey: "id_aluno",
			sourceKey: "id",
		});
		Matricula.belongsTo(models.Curso, {
			foreignKey: "id_curso",
			sourceKey: "id",
		});
	};

	return Matricula;
};
