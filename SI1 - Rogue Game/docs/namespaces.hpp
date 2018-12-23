//! \namespace RG
/*!
 *  \brief Main namespace of the game.
 *
 *  Game is using MVC architecture and so it has namespace RG::Model, RG::View and RG::Controller. There is also RG::NPC whitch includes trading worldd and basically is another part of Model. Namespace RF::Util includes some usefull utilities.
 */
namespace RG {

    //! \namespace RG::Model
    /*!
     *  \brief This namespace includes game entities.
     *
     *  This is model of our game. It includes all date about game entitie, for example Floor or Player. Model also manages physic engine of game.
     */
    namespace Model {}

    //! \namespace RG::View
    /*!
     *  \brief This namespace includes "frontend" of the game.
     *
     *  View is resposible for managing player input and presenting him data from Model. It has some classes whitch mirror classes in Model, for exaple Player. But these classes are used only for user input and drawing data from model. If they store any data, then these date connected just  to graphics, for example texture.
     */
    namespace View {}

    //! \namespace RG::Controller
    /*!
     *  \brief This namespace includes Controller of the game.
     *
     *  Controller is used to send date from View to model and extract data from model for View.
     */
    namespace Controller {}

    //! \namespace RG::NPC
    /*!
     *  \brief Namespace used for trading items and assigning work to NPC's.
     *
     *  NPC namespace contains marketplace class used for trading items between player and NPC's and between NPC themselves.
     *  Each NPC has their own intelligence and each NPC works and or creates Items.
     *  Matching of trades is done via MatchingEngine class.
     *  NPCWorldCycle is used as a interface for communicating between Controller namespace and NPC namespace.
     */
    namespace NPC {}

    //! \namespace RG::Util
    /*!
     *  \brief This namespace includes some usefull utileties whitch are used in all part of the game.
     */
    namespace Util {}
}
