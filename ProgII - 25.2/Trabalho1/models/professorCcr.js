"use strict";

module.exports = (sequelize, DataTypes) => {
	const ProfessorCcr = sequelize.define(
		"ProfessorCcr",
		{
			id_professor: {
				type: DataTypes.INTEGER,
				primaryKey: true,
			},
			id_ccr: {
				type: DataTypes.INTEGER,
				primaryKey: true,
			},
		},
		{
			sequelize,
			tableName: "professorCcr",
			schema: "public",
			freezeTableName: true,
			timestamps: false,
		},
	);

	ProfessorCcr.associate = function (models) {
		ProfessorCcr.belongsTo(models.Professor, {
			foreignKey: "id_professor",
			sourceKey: "id",
		});
		ProfessorCcr.belongsTo(models.Ccr, {
			foreignKey: "id_ccr",
			sourceKey: "id",
		});
	};

	return ProfessorCcr;
};
