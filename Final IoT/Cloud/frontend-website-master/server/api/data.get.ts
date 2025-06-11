import { getRedisClient } from '~/server/redis'

export default defineEventHandler(async () => {
    const redis = await getRedisClient()

    const tilt = await redis.get('T')
    const photor = await redis.get('P')

    const dist = await redis.get('Percen_capa')
    const temp = await redis.get('Temperature')

    const history = await redis.get('disthistory')

    const jsonObj = JSON.parse(history || '{}')

    const fanState = await redis.get('fanState') === '1'

    return {
        tilted: tilt === '1',
        lidOpen: photor === '1',
        photoresistor: parseInt(photor || '0'),
        capacity: parseInt(dist || '0'),
        temperature: parseInt(temp || '0'),
        fanState: fanState,
        history: jsonObj,
    }
})
