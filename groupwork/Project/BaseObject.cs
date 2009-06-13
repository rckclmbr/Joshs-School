using System;

namespace ATM.BLL
{
    public abstract class BaseObject
    {
        private ObjectStatus _objectStatus = ObjectStatus.New;

        public ObjectStatus Status
        {
            get { return _objectStatus; }
            set { _objectStatus = value; }
        }

		protected BaseObject( )
		{
            
        }

        protected BaseObject(BaseObject status)
		{
            _objectStatus = status._objectStatus;
		}

        protected BaseObject(ObjectStatus objectStatus)
		{
            _objectStatus = objectStatus;
		}

        protected virtual void dirty()
        {
            if (_objectStatus == ObjectStatus.Clean)
            {
                _objectStatus = ObjectStatus.Dirty;
            }
        }

    }
}
