"use strict";

module.exports = (sequelize, DataTypes) => {
	const Professor = sequelize.define(
		"Professor",
		{
			id: {
				type: DataTypes.INTEGER,
				autoincrement: true,
				primaryKey: true,
			},
			nome: DataTypes.STRING,
			email: DataTypes.STRING,
		},
		{
			sequelize,
			tableName: "professor",
			schema: "public",
			freezeTableName: true,
			timestamps: false,
		},
	);

	Professor.associate = function (models) {
		Professor.hasMany(models.ProfessorCcr, {
			foreignKey: "id_professor",
			sourceKey: "id",
		});
	};

	return Professor;
};
