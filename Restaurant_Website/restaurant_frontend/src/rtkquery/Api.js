import { createApi, fetchBaseQuery } from "@reduxjs/toolkit/query/react";

const api = createApi({
    reducerPath:'menuApi',
    baseQuery: fetchBaseQuery({
        baseUrl:'http://localhost:5000/'
       /* prepareHeaders:(headers)=>
        {
            const saved =localStorage.getItem("d") || "";
            const token= JSON.parse(saved);
            if(token)
            {
                headers.set('authorization',`${token.token}`);
            }
        }*/
    }),
    endpoints: (build)=>({
        addUsers:build.mutation({
            query:(user)=>({
            url:'api/register', 
            method:'POST',
            body:user
            })
        }),
        loginUser:build.mutation({
            query:(user)=>({
                url:'api/login',
                method:'POST',
                body:user
            })
        }),
        reserveTable:build.mutation({
            query:(data)=>({
                url:`api/reserve/${data.uid}`,
                method:'POST',
                body:data
            })
        }),
        makeOrder:build.mutation({
            query:(data)=>({
                url:`api/makeorder/${data.rid}`,
                method:'POST',
                body:data
            })
        }),
        createTable:build.mutation({
            query:(capacity)=>({
                url:'api/createtable',
                method:'POST',
                body:{capacity}
            })
        }),
        createMenu:build.mutation({
            query:(formData)=>({
                url:'api/createmenu',
                method:'POST',
                body:formData,
                formData:true
            })
        }),
        getUser:build.query({
            query:(email)=>(`api/getuserid/${email}`)
        }),
        getAllReservations:build.query({
            query:()=>('api/getreservations')
        }),
        getReservationsById:build.query({
            query:(uid)=>(`api/getreservationsbyid/${uid}`)
        }),
        getMenuByCategory:build.query({
            query:(category)=>(`api/getmenu?category=${category}`)
        })
    })
});

export const {useAddUsersMutation,useLoginUserMutation,useReserveTableMutation,useGetUserQuery,useGetAllReservationsQuery,useMakeOrderMutation,useGetReservationsByIdQuery,useCreateTableMutation,useCreateMenuMutation,useGetMenuByCategoryQuery} = api;
export default api;