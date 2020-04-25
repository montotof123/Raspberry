// https://sequelize.org/v5/manual/models-definition.html#configuration
// https://sequelize.org/v5/manual/data-types.html

// Modele de la table PostgreSQL meteo
module.exports = (sequelize, Sequelize) => {
  const Meteo = sequelize.define('meteo', {
    horaire: {
      type: Sequelize.DATE,
      primaryKey: true,
      field: 'horaire',
      allowNull: false
    },
    temperature: {
      type: Sequelize.DECIMAL(4,2),
      field: 'temperature',
      allowNull: false
    },
    pressionBrute: {
      type: Sequelize.DECIMAL(6,2),
      field: 'pression_brute',
      allowNull: false
    },
    pressionNiveauMer: {
      type: Sequelize.DECIMAL(6,2),
      field: 'pression_niveau_mer',
      allowNull: false
    },
    altitude: {
      type: Sequelize.DECIMAL(8,2),
      field: 'altitude',
      allowNull: false
    },
    humidite: {
      type: Sequelize.DECIMAL(4,2),
      field: 'humidite',
      allowNull: false
    },
  }, 
  { freezeTableName: true,
    // Evite la creation des champs created_at et updated_at dans la table
    timestamps: false,
    // Evite les log dans la console
    // silent: true,
    underscored: false }
  );
  console.log(Meteo);
  return Meteo;
};
