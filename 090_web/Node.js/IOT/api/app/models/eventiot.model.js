// https://sequelize.org/v5/manual/models-definition.html#configuration
// https://sequelize.org/v5/manual/data-types.html

// Modele de la table PostgreSQL eventIOT
module.exports = (sequelize, Sequelize) => {
  const EventIOT = sequelize.define('eventiot', {
    horaire: {
      type: Sequelize.DATE,
      primaryKey: true,
      field: 'horaire',
      allowNull: false
    },
    id: {
      type: Sequelize.STRING,
      field: 'id',
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
  return EventIOT;
};
