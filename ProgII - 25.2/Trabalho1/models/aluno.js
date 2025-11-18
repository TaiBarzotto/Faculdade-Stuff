"use strict";

module.exports = (sequelize, DataTypes) => {
	const Aluno = sequelize.define(
		"Aluno",
		{
			id: {
				type: DataTypes.INTEGER,
				autoIncrement: true,
				primaryKey: true,
			},
			nome: DataTypes.STRING,
			email: DataTypes.STRING,
		},
		{
			sequelize,
			tableName: "aluno",
			schema: "public",
			freezeTableName: true,
			timestamps: false,
		},
	);

	Aluno.associate = function (models) {
		Aluno.hasMany(models.Matricula, {
			foreignKey: "id_aluno",
			sourceKey: "id",
		});
	};

	return Aluno;
};
