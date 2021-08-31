using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using GestDep.Entities;

namespace GestDep.Services
{
    public interface IGestDepService
    {
        
        #region Add new activity
        /// <summary>
        /// Adds a news activity
        /// </summary>
        /// <param name="activityDays"></param>
        /// <param name="description"></param>
        /// <param name="duration"></param>
        /// <param name="finishDate"></param>
        /// <param name="maximumEnrollments"></param>
        /// <param name="minimumEnrollments"></param>
        /// <param name="price"></param>
        /// <param name="startDate"></param>
        /// <param name="startHour"></param>
        /// <param name="roomsIds"></param>
        /// <returns>Id of the new activity</returns>
        /// <exception cref="ServiceException">Thrown when no available room exists, the date and time ranges are not valid, or the activity is programmed to start before now.</exception> 
        int AddNewActivity(Days activityDays, String description, TimeSpan duration, DateTime finishDate,
            int maximumEnrollments, int minimumEnrollments, double price,
            DateTime startDate, DateTime startHour, ICollection<int> roomsIds);

        /// <summary>
        /// Lists all rooms that are available for use in the given time frame.
        /// </summary>
        /// <param name="activityDays"></param>
        /// <param name="startDate"></param>
        /// <param name="finishDate"></param>
        /// <param name="startHour"></param>
        /// <param name="finishHour"></param>
        /// <returns>A collection of room ids</returns>
        /// <exception cref="ServiceException">Thrown when no available room exists or the date and time ranges are not valid.</exception>
        ICollection<int> GetListAvailableRoomsIds(Days activityDays, TimeSpan duration, DateTime finishDate, DateTime startDate, DateTime startHour);

        /// <summary>
        /// Gets the room data for the given id.
        /// </summary>
        /// <param name="roomId"></param>
        /// <param name="number"></param>
        /// <param name="activityIds">If there are no activities scheduled to take place in the room, returns an empty ICollection of int.</param>
        /// <exception cref="ServiceException">Thrown when the room doesn't exist.</exception>
        void GetRoomDataFromId(int roomId, out int number, out ICollection<int> activityIds);
        #endregion
        #region Assign instructor to activity.
        /// <summary>
        /// Gets the activity data for the given id.
        /// </summary>
        /// <param name="ActivityId"></param>
        /// <param name="activityDays"></param>
        /// <param name="description"></param>
        /// <param name="duration"></param>
        /// <param name="finishDate"></param>
        /// <param name="maximumEnrollments"></param>
        /// <param name="minimumEnrollments"></param>
        /// <param name="price"></param>
        /// <param name="startDate"></param>
        /// <param name="startHour"></param>
        /// <param name="enrollmentIds">If no enrollment has been added, returns an empty list.</param>
        /// <param name="instructorId">If no instructor has been set, returns an empty string.</param>
        /// <param name="roomIds">If no room has been added, returns an empty list.</param>
        /// <exception cref="ServiceException">Thrown when the activity doesn't exist.</exception> 
        void GetActivityDataFromId(int ActivityId, out Days activityDays, out String description, out TimeSpan duration, 
            out DateTime finishDate, out int maximumEnrollments, out int minimumEnrollments, out double price,
            out DateTime startDate, out DateTime startHour, out ICollection<int> enrollmentIds, 
            out String instructorId, out ICollection<int> roomIds);

        /// <summary>
        /// Gets all activities ids.
        /// </summary>
        /// <returns>A list of activity ids.</returns>
        ICollection<int> GetAllActivitiesIds();


        /// <summary>
        /// Gets the instructor data for the given id.
        /// </summary>
        /// <param name="instructorId"></param>
        /// <param name="address"></param>
        /// <param name="IBAN"></param>
        /// <param name="name"></param>
        /// <param name="zipCode"></param>
        /// <param name="ssn"></param>
        /// <param name="activitiesIds">If the instructor doesn't teach any activity, returns an empty ICollection of int</param>
        /// <exception cref="ServiceException">Thrown when the instructor doesn't exist.</exception>
        void GetInstructorDataFromId(string instructorId, out String address, out String IBAN, out String name, out int zipCode,
            out String ssn, out ICollection<int> activitiesIds);

        /// <summary>
        /// Gets all instructors that are available in the given time frame.
        /// </summary>
        /// <param name="activityDays"></param>
        /// <param name="startDate"></param>
        /// <param name="finishDate"></param>
        /// <param name="startHour"></param>
        /// <returns>A list of instructor ids (string)</returns>
        /// <exception cref="ServiceException">Thrown when there are not available instructors or the date and time ranges are not valid.</exception> 
        ICollection<string> GetAvailableInstructorsIds(Days activityDays, TimeSpan duration, DateTime finishDate, DateTime startDate, DateTime startHour);

        /// <summary>
        /// Assigns an instructor to an activity
        /// </summary>
        /// <param name="activityId"></param>
        /// <param name="instructorId"></param>
        /// <exception cref="ServiceException">Thrown when either the instructor id or activity id don't exist.</exception>
        void AssignInstructorToActivity(int activityId, string instructorId);
        #endregion
        #region Enroll into activity
        /// <summary>
        /// Gets all activities that are currently running or will run in the future.
        /// </summary>
        /// <returns>A list of actitity ids</returns>
        /// <exception cref="ServiceException">Thrown when there are not activities planned or running.</exception> 
        ICollection<int> GetAllRunningOrFutureActivitiesIds();

        /// <summary>
        /// Gets all user data for the given id.
        /// </summary>
        /// <param name="userId"></param>
        /// <param name="address"></param>
        /// <param name="iban"></param>
        /// <param name="name"></param>
        /// <param name="zipCode"></param>
        /// <param name="birthDate"></param>
        /// <param name="retired"></param>
        /// <param name="enrollmentIds">If the user is not enrolled in any activity, returns an empty ICollection of int.</param>
        /// <exception cref="ServiceException">Thrown when there are no users with this Id.</exception> 
        void GetUserDataFromId(string userId, out string address, out string iban, out string name, out int zipCode,
            out DateTime birthDate, out bool retired, out ICollection<int> enrollmentIds);

        /// <summary>
        /// Gets all user data for the given id, but also checks that the user is no already enrolled in that activity.
        /// </summary>
        /// <param name="activityId"></param>
        /// <param name="userId"></param>
        /// <param name="address"></param>
        /// <param name="iban"></param>
        /// <param name="name"></param>
        /// <param name="zipCode"></param>
        /// <param name="birthDate"></param>
        /// <param name="retired"></param>
        /// <param name="enrollmentIds">If the user is not enrolled in any activity, returns an empty ICollection of int.</param>
        /// <returns>Returns the first quota</returns>
        /// <exception cref="ServiceException">Thrown when the user is already enrolled in the activity or the user or the activity don't exist (requires two different message exceptions).</exception>
        double GetUserDataNotInActivityAndFirstQuota(int activityId, string userId, out string address, out string iban, 
            out string name, out int zipCode,
            out DateTime birthDate, out bool retired, out ICollection<int> enrollmentIds);

        /// <summary>
        /// Enrolls a user in an activity.
        /// </summary>
        /// <param name="activityId"></param>
        /// <param name="userId"></param>
        /// <returns>Returns the id of the generated enrollment.</returns>
        /// <exception cref="ServiceException">Thrown when either the user id or activity id don't exist.</exception>
        int EnrollUserInActivity(int activityId, string userId);

        /// <summary>
        /// Gets all enrollment data for the given activity and enrollment ids
        /// </summary>
        /// / <param name="activityId"></param>
        /// <param name="enrollmentId"></param>
        /// <param name="cancellationDate"></param>
        /// <param name="enrollmentDate"></param>
        /// <param name="returnedFirstCuotaIfCancelledActivity"></param>
        /// <param name="activityId"></param>
        /// <param name="paymentIds"></param>
        /// <param name="userId"></param>
        /// <exception cref="ServiceException">Thrown when the enrollment doesn't exist.</exception> 
        void GetEnrollmentDataFromIds(int activityId, int enrollmentId, out DateTime? cancellationDate, out DateTime enrollmentDate,
            out DateTime? returnedFirstCuotaIfCancelledActivity, out ICollection<int> paymentIds, 
            out string userId);

        /// <summary>
        /// Gets all payment data for the given id.
        /// </summary>
        /// <param name="paymentId"></param>
        /// <param name="date"></param>
        /// <param name="description"></param>
        /// <param name="quantity"></param>
        /// <exception cref="ServiceException">Thrown when the payment doesn't exist.</exception> 
        void GetPaymentDataFromId(int paymentId, out DateTime date, out string description, out double quantity);
        #endregion
        #region Add new user
        /// <summary>
        /// 
        /// </summary>
        /// <param name="address"></param>
        /// <param name="iban"></param>
        /// <param name="id"></param>
        /// <param name="name"></param>
        /// <param name="zipCode"></param>
        /// <param name="birthDate"></param>
        /// <param name="retired"></param>
        /// <exception cref="ServiceException">Thrown when the user already exists or when the provided data is not valid (for instance, the birth date is after the current instant).</exception> 
        void AddNewUser(string address, string iban, string id, string name, int zipCode, DateTime birthDate, bool retired);
        #endregion
        #region List free rooms in week.
        /// <summary>
        /// Gets all available rooms per time frame per week.
        /// </summary>
        /// <param name="initialMonday"></param>
        /// <returns>A dictionary with all time slots in the week with the number of rooms available at that moment.</returns>
        /// <exception cref="ServiceException">Thrown when the selected date is not a monday.</exception>
        Dictionary<DateTime, int> GetListAvailableRoomsPerWeek(DateTime initialMonday);
        
        /// <summary>
        /// Returns the data of the gym of the CityHall (services work with only one gym)
        /// </summary>
        /// <param name="gymId"></param>
        /// <param name="closingHour"></param>
        /// <param name="discountLocal"></param>
        /// <param name="discountRetired"></param>
        /// <param name="freeUserPrice"></param>
        /// <param name="name"></param>
        /// <param name="openingHour"></param>
        /// <param name="zipCode"></param>
        /// <param name="activityIds">If no activity has been added, returns an empty ICollection of int</param>
        /// <param name="roomIds">If no room has been added, returns an empty ICollection of int</param>
        /// <exception cref="ServiceException">Thrown when the cityHall has no gym.</exception>
        void GetGymData( out int  gymId, out DateTime closingHour, out int discountLocal, out int discountRetired, out double freeUserPrice,
                    out String name, out DateTime openingHour, out int zipCode, out ICollection<int> activityIds, out ICollection<int> roomIds);

        #endregion
        #region Others
        /// <summary>
        /// Removes all data from the database.
        /// </summary>
        void RemoveAllData();

        /// <summary>
        /// Saves all modified entities.
        /// </summary>
        void SaveChanges();
        #endregion
    }
}
