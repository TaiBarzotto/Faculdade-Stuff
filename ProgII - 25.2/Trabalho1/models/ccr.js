"use strict";

module.exports = (sequelize, DataTypes) => {
	const Ccr = sequelize.define(
		"Ccr",
		{
			id: {
				type: DataTypes.INTEGER,
				primaryKey: true,
			},
            descricao: DataTypes.STRING,
            ementa: DataTypes.STRING,
            id_curso:{
                type: DataTypes.INTEGER,
                foreignKey: true,
            }
		},
		{
			sequelize,
			tableName: "ccr",
			schema: "public",
			freezeTableName: true,
			timestamps: false,
		},
	);

	Ccr.associate = function (models) {
		Ccr.belongTo(models.Curso, {
			foreignKey: "id_curso",
			sourceKey: "id",
		});
	};

	return Ccr;
};
